#Writes mgsvtpp_patterns.h
#using function names defined in ExportInfo.py
#edit hDestPath to change export location
#takes a long time to run because t0 checks to see if pattern has no other matches
#@author tex, pattern function by nosoop
#@category IHHook
#@keybinding 
#@menupath 
#@toolbar 

#adapted from:
#https://forums.alliedmods.net/showthread.php?t=321815
#https://github.com/nosoop/ghidra_scripts/blob/master/makesig.py

#BSD zero clause licence
#Copyright (c) 2020 nosoop
#
#Permission to use, copy, modify, and/or distribute this software for any
#purpose with or without fee is hereby granted.
#
#THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
#REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
#AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
#INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
#LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
#OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#PERFORMANCE OF THIS SOFTWARE.

#tex TODO: options export/update all, export only missing/new
#TODO: build to an intermediate python table so it can figure out what has/hasn't been updated.

from __future__ import print_function
from java.io import PrintWriter
from ExportInfo import * #ExportInfo.py for exportInfo list

import collections
import ghidra.program.model.lang.OperandType as OperandType
import ghidra.program.model.lang.Register as Register
import ghidra.program.model.address.AddressSet as AddressSet

hDestPath="D:/GitHub/IHHook/IHHook/"#tex TODO: filechooser? but I dont like the extra step it would take for something thats static (and ghidra doesnt remember per-script last-chosen)

exeName="mgsvtpp"

#tex config
wildcardHex=r'\x00' #tex

#tex TODO: im duplicating some stuff between scripts here
#tex using exportInfo to give order
infoLookup={}
for idx, entry in enumerate(exportInfo):
	infoLookup[entry["name"]]=idx

#test#for name in infoLookup:
	#print(name)

def getinfo(name):
	idx=infoLookup[name]
	return exportInfo[idx]

#test#print(getinfo("luaopen_string"))

numFound=0
listing = currentProgram.getListing();

#tex would be a lot easier if I could get
#functions=listing.getFunctions(None,entry["name"])
#to return matches

foundFunctions={}
for function in listing.getFunctions(True):
	if not function.isThunk():
		idx=infoLookup.get(function.getName())
		if idx!=None:
			#test#print("found " + function.getName())
			foundFunctions[function.getName()]=function



#################

MAKE_SIG_AT = collections.OrderedDict([
	('fn', 'start of function'),
	('cursor', 'instruction at cursor')
])

BytePattern = collections.namedtuple('BytePattern', ['is_wildcard', 'byte'])

def __bytepattern_ida_str(self):
	# return an IDA-style binary search string
	return '{:02X}'.format(self.byte) if not self.is_wildcard else '?'

def __bytepattern_sig_str(self):
	# return a SourceMod-style byte signature
	return r'\x{:02X}'.format(self.byte) if not self.is_wildcard else wildcardHex #tex wildcardHex was r'\x2A' to get around \x00 being null term for string, but what I see about SourceMod signatures is it uses the normal \x00 so how does it get round that

BytePattern.ida_str = __bytepattern_ida_str
BytePattern.sig_str = __bytepattern_sig_str

def dumpOperandInfo(ins, op):
	t = hex(ins.getOperandType(op))
	print('  ' + str(ins.getPrototype().getOperandValueMask(op)) + ' ' + str(t))
	
	# TODO if register
	for opobj in ins.getOpObjects(op):
		print('  - ' + str(opobj))

def shouldMaskOperand(ins, opIndex):
	"""
	Returns True if the given instruction operand mask should be masked in the signature.
	"""
	optype = ins.getOperandType(opIndex)
	# if any(reg.getName() == "EBP" for reg in filter(lambda op: isinstance(op, Register), ins.getOpObjects(opIndex))):
		# return False
	return optype & OperandType.DYNAMIC or optype & OperandType.ADDRESS

def getMaskedInstruction(ins):
	"""
	Returns a generator that outputs either a byte to match or None if the byte should be masked.
	"""
	# print(ins)
	
	# resulting mask should match the instruction length
	mask = [0] * ins.length
	
	proto = ins.getPrototype()
	# iterate over operands and mask bytes
	for op in range(proto.getNumOperands()):
		# dumpOperandInfo(ins, op)
		
		# TODO deal with partial byte masks
		if shouldMaskOperand(ins, op):
			mask = [ m | v & 0xFF for m, v in zip(mask, proto.getOperandValueMask(op).getBytes()) ]
	# print('  ' + str(mask))
	
	for m, b in zip(mask, ins.getBytes()):
		if m == 0xFF:
			# we only check for fully masked bytes at the moment
			yield BytePattern(is_wildcard = True, byte = None)
		else:
			yield BytePattern(byte = b & 0xFF, is_wildcard = False)

def CreatePattern(startAddress):
	
	fm = currentProgram.getFunctionManager()
	#fn = fm.getFunctionContaining(currentAddress)
	fn = fm.getFunctionContaining(startAddress)
	cm = currentProgram.getCodeManager()

	#was CULL
	#if start_at == MAKE_SIG_AT['fn']:
	#	ins = cm.getInstructionAt(fn.getEntryPoint())
	#elif start_at == MAKE_SIG_AT['cursor']:
	#	ins = cm.getInstructionContaining(currentAddress)

	ins = cm.getInstructionContaining(startAddress)
	
	if not ins:
		raise Exception("Could not find entry point to function")

	pattern = "" # contains pattern string (supports regular expressions)
	byte_pattern = [] # contains BytePattern instances
	
	# keep track of our matches
	matches = []
	match_limit = 128
	
	while fm.getFunctionContaining(ins.getAddress()) == fn:
		for entry in getMaskedInstruction(ins):
			byte_pattern.append(entry)
			if entry.is_wildcard:
				pattern += '.'
			else:
				pattern += r'\x{:02x}'.format(entry.byte)
		
		expected_next = ins.getAddress().add(ins.length)
		ins = ins.getNext()
		
		if ins.getAddress() != expected_next:
			# we don't have a good way to deal with alignment bytes
			# raise an exception for now
			err = "WARNING: "+fn.getName() + ": Instruction at %s is not adjacent to previous (expected %s)" % (expected_next, ins.getAddress())
			print(err)
			return {"pattern":"","err":err}
		
		if 0 < len(matches) < match_limit:
			# we have all the remaining matches, start only searching those addresses
			match_set = AddressSet()
			for addr in matches:
				match_set.add(addr, addr.add(len(byte_pattern)))
			matches = findBytes(match_set, pattern, match_limit, 1)
		else:
			# the matches are sorted in ascending order, so the first match will be the start
			matches = findBytes(matches[0] if len(matches) else None, pattern, match_limit)
		
		if len(matches) < 2:
			break
	
	pattern=""
	for b in byte_pattern:
		pattern = pattern + b.ida_str() + " "
	pattern = pattern.rstrip()

	if not len(matches) == 1:
		print("WARNING: " + fn.getName() + ":" + pattern)
		#print(*(b.ida_str() for b in byte_pattern))
		print('Pattern matched', len(matches), 'locations:', *(matches))
		print("Could not find unique Pattern")
		err = "WARNING: Could not find unique Pattern, found " + str(len(matches)) + " matches"
	else:
		#print("Pattern for", fn.getName())
		#print(*(b.ida_str() for b in byte_pattern))
		#OFF print("".join(b.sig_str() for b in byte_pattern))
		print(fn.getName() + ":" + pattern)
		err=""
	return {"pattern":pattern,"err":err}

######
def BuildPatterns():
	lines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		reason=""
		pattern=""
		if noAddress!=None:
			reason=noAddress
		else:
			function=foundFunctions.get(name)
			#print("function:"+str(function))
			if function==None:
				reason="WARNING: function NOT_FOUND"
			else:
				#TODO: inter function start point
				startAddress=function.getEntryPoint() 
				ret=CreatePattern(startAddress)
				pattern = ret["pattern"]
				err = ret["err"]
				if err!="":
					reason=err

		#REF output
		#{"StrCode64", "48 89 ? ? ? 56 48 83 EC ? 80 3C 0A"},
		line='{"'+name+'", "'+str(pattern)+'"},'
		if pattern=="":
			line="//"+line
		if reason!="":
			line=line+"//"+reason

		lines.append(line)
		#print(line)
	return lines

def WritePatternHFile():
	#fileName=exeName+"_patterns_"+version+"_"+lang
	fileName=exeName+"_patterns"
	headerFilePath=hDestPath+fileName+".h"

	patternLines=BuildPatterns()
	print("---")

	header=[
		"#pragma once",
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//GOTCHA: while in theory updates to exe could change function enough to break signature",
		"//that's a case of deal with it if it happens (and the point of patterns is that its less likely)",
		"//and in the meantime this header/ihhook doesnt have a per exe version system for patterns",
		"//(though was built from 1.0.15.3)",
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	hLines=[]

	for line in header:
		hLines.append(line)

	hLines.append("namespace IHHook {")
	hLines.append("\t"+"std::map<std::string, std::string> "+fileName+"{")

	for line in patternLines:
		hLines.append("\t\t"+line)

	hLines.append("\t};//map "+fileName)
	hLines.append("}//namespace IHHook")

	file = PrintWriter(headerFilePath);
	for line in hLines:
		file.println(line)
		print(line)

	file.flush()
	file.close()


#####
#exec
print("---")
#patternLines=BuildPatterns()
#for line in patternLines:
	#print(line)

WritePatternHFile()
