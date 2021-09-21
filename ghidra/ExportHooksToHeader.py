#Writes mgsvtpp_adresses_<version>_<lang>.h and mgsvtpp_func_typedefs.h
#using function names defined in ExportInfo.py
#edit hDestPath to change export location
#@author tex
#@category IHHook
#@keybinding 
#@menupath 
#@toolbar 

from java.io import PrintWriter
from ExportInfo import * #ExportInfo.py for exportInfo list

hDestPath="D:/GitHub/IHHook/IHHook/"#tex TODO: filechooser? but I dont like the extra step it would take for something thats static (and ghidra doesnt remember per-script last-chosen)

version="1_0_15_3"
exeName="mgsvtpp"

#Don't need to change anything past here

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

#TODO: fill out typedefs for noAddress that have found functions anyway? (but still have them commented them out)
def BuildSignatures():
	signatureLines=[]
	typedefLines=[]

	for entry in exportInfo:
		name=entry["name"]

		noAddress=entry.get("noAddress")
		address=""
		invalidReason=None
		signatureLine=""#not actually output, just a pretty-printed/normal declaration of the function
		typedefLine=""
		if noAddress!=None:
			invalidReason=noAddress
		else:
			function=foundFunctions.get(name)
			if function==None:
				invalidReason="NOT_FOUND"
			else:
				address=""
				#print(function.getName())
				signature=function.getSignature()
				#print(signature.getPrototypeString())
				ret=signature.getReturnType().getName()
				arguments=signature.getArguments()
				signatureLine=ret+" "+name
				typedefLine="typedef "+ret+" (__fastcall "+name+"Func)("#TODO: pull calling convention too?
				#WORKAROUND: tex ghidra signature doesnt have const keyword
				noConstChar=entry.get("noConstChar")#tex currently will apply const to char * by default, or noConstChar to skip TODO: don't know which is the most common/to have as default. in general you use const char* for string literals and char* for buffers/actual mutable strings
				constParams=entry.get("constParams")#WORKAROUND: per param const declaration
				for idx,parameter in enumerate(arguments):
					paramName=parameter.getName()
					dataTypeName=parameter.getDataType().getName()
					#print(paramName)
					#print(dataTypeName)
					if noConstChar==None:
						if dataTypeName=="char *":
							dataTypeName="const "+dataTypeName
					if constParams!=None:
						for constParam in constParams:
							#print(constParam)
							if constParam==paramName:
								dataTypeName="const "+dataTypeName
								break
					signatureLine=signatureLine+dataTypeName+" "+paramName
					typedefLine=typedefLine+dataTypeName+" "+paramName
					if idx!=len(arguments)-1:
						signatureLine=signatureLine+", "
						typedefLine=typedefLine+", "
				signatureLine=signatureLine+");"
				typedefLine=typedefLine+");"
				signatureLines.append(signatureLines)
				typedefLines.append(typedefLine)
		if invalidReason!=None:
			signatureLine="// "+name+" "+invalidReason
			typedefLine=signatureLine
			signatureLines.append(signatureLines)
			typedefLines.append(typedefLine)

		#print(signatureLine)
		#print(typedefLine)
	return typedefLines

def BuildExternPointers():
	lines=[]
	for entry in exportInfo:
		name=entry["name"]
		noAddress=entry.get("noAddress")
		invalidReason=None
		if noAddress!=None:
			invalidReason=noAddress
		else:
			function=foundFunctions.get(name)
			if function==None:
				invalidReason="NOT_FOUND"

		externLine="extern "+name+"Func* "+name+";"

		if invalidReason!=None:
			lines.append("//"+externLine+"//"+invalidReason)
		else:
			lines.append(externLine)
	return lines

def BuildAddressMap():
	outLines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		note=entry.get("note")
		address=""
		invalid=False
		if noAddress!=None:
			address=noAddress
			invalid=True
		else:
			function=foundFunctions.get(name)
			#print("function:"+str(function))
			if function==None:
				address="NOT_FOUND"
				invalid=True
			else:
				address="0x"+str(function.getEntryPoint())
		if note==None:
			note=""
		else:
			note="//"+note

		commentOut=""
		if invalid:
			commentOut="//"

		#address map
		#REF output
		#{"StrCode64", 0x14c1bd730},
		line=commentOut+'{"'+name+'", '+str(address)+'},'+note
		outLines.append(line)
		#print(line)
	return outLines

def WriteAddressHFile():
	fileName=exeName+"_adresses_"+version+"_"+lang
	headerFilePath=hDestPath+fileName+".h"

	addressLines=BuildAddressMap()

	header=[
		"#pragma once",
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	hLines=[]

	for line in header:
		hLines.append(line)

	hLines.append("namespace IHHook {")
	hLines.append("\t"+"std::map<std::string, int64_t> "+fileName+"{")

	for line in addressLines:
		hLines.append("\t\t"+line)

	hLines.append("\t};//map "+fileName)
	hLines.append("}//namespace IHHook")

	file = PrintWriter(headerFilePath);
	for line in hLines:
		file.println(line)
		print(line)

	file.flush()
	file.close()

def WriteFuncTypeDefHFile():
	fileName=exeName+"_func_typedefs"
	headerFilePath=hDestPath+fileName+".h"

	signatures=BuildSignatures()
	externPointersLines=BuildExternPointers()

	header=[
		"#pragma once",
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"",
		"//GOTCHA: ghidra signature doesnt have const keyword",
	]

	#TODO: is a per category thing
	includes=[
		'#include "lua/lua.h"',
		'#include "lua/lauxlib.h"',
	]

	macros=[
		"//macros for ghidra data type names > c++",
		"#define longlong long long",
		"#define ulonglong unsigned long long",
		"#define uint unsigned int",
	]

	file = PrintWriter(headerFilePath);
	for line in header:
		file.println(line)
	file.println("")
	for line in includes:
		file.println(line)
	file.println("")
	for line in macros:
		file.println(line)
	file.println("")
	for line in signatures:
		file.println(line)
		print(line)
	file.println("")
	file.println("//tex the (extern of the) function pointers")
	for line in externPointersLines:
		file.println(line)
		print(line)
	file.println("")

	file.flush()
	file.close()

#exec
lang = askChoice("ExportHooksToHeader", "Select lang of this exe:", ["en","jp"], "en")

print("----")
WriteAddressHFile()
print("----")
WriteFuncTypeDefHFile()

