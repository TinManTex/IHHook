#Writes mgsvtpp_adresses_<version>_<lang>.h, mgsvtpp_func_typedefs.h, mgsvtpp_funcptr_defs.cpp
#using function names defined in ExportInfo.py
#edit hDestPath to change export location
#@author tex
#@category IHHook
#@keybinding 
#@menupath 
#@toolbar 

#TODO: this has a lot of redundancy in the build/write functions

import os
from java.io import PrintWriter
from ExportInfo import * #ExportInfo.py for exportInfo list

#tex should be to repo root, 
# rather than editing this a user should copy ExportPath_User.py to ghidra program folder and edit path.
hDestPath='D:/GitHub/IHHook/'
hDestSubPath='IHHook/hooks/'#tex only should be changed if the ihhook project changes the location
print('hDestPath: initial ' + hDestPath)
hUserFile='./ExportPath_User.py'

version="1_0_15_3"
exeName="mgsvtpp"

debugmode=True #enables debugprints

#except for hUserFile, any of the above can be overridden by ExportPath_User.py
#Don't need to change any settings past here


cwd = os.getcwd()
#print("Current working directory: {0}".format(cwd))

if os.path.isfile(hUserFile):
	with open(hUserFile) as f:
		all = f.read()
		exec(all)
else:
	print(hUserFile + " not found in " + cwd + " using hDestPath: " + hDestPath)

hDestPath = hDestPath + hDestSubPath

print('using hDestPath: ' + hDestPath)

#only print if debugmode true
def debugprint(message):
	if debugprint:
		print(message)

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

#Build function typdef from ghidra function signature
#TODO: fill out typedefs for noAddress that have found functions anyway? (but still have them commented them out)
def BuildSignatures():
	signatureLines=[]#unused
	typedefLines=[]

	for entry in exportInfo:
		name=entry["name"]

		noAddress=entry.get("noAddress")
		exportFunc=entry.get("exportFunc")
		address=""
		invalidReason=None
		signatureLine=""#not actually output, just a pretty-printed/normal declaration of the function
		typedefLine=""
		if noAddress!=None:
			invalidReason=noAddress
		elif exportFunc==False:
			invalidReason="EXPORT_FUNC_FALSE"
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
				callConvention=signature.getGenericCallingConvention().getDeclarationName() #ZIP: Added calling convention support
				if callConvention=="":
						callConvention="__fastcall"
				typedefLine="typedef "+ret+" ("+callConvention+" "+name+"Func)("
				#WORKAROUND: tex ghidra signature doesnt have const keyword
				constCharPtr=entry.get("constCharPtr")#tex currently will apply const to char * by default, or constCharPtr:False to skip TODO: don't know which is the most common/to have as default. in general you use const char* for string literals and char* for buffers/actual mutable strings
				constParams=entry.get("constParams")#WORKAROUND: per param const declaration
				for idx,parameter in enumerate(arguments):
					paramName=parameter.getName()
					dataTypeName=parameter.getDataType().getName()
					#print(paramName)
					#print(dataTypeName)
					if callConvention=="__thiscall" and paramName=="this":
						paramName="This"#WORKAROUND ZIP: Fixes "this" param in __thiscall
					if constCharPtr!=False:
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
				if function.hasVarArgs()==True:
					signatureLine=signatureLine+", ..."
					typedefLine=typedefLine+", ..."
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
	outLines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		exportFunc=entry.get("exportFunc")
		reason=None
		if noAddress!=None:
			reason=noAddress
		#elif exportFunc==False:
			#reason="EXPORT_FUNC_FALSE"	#TODO: don't know if I want to have to handle this in func_typedefs_manual.h	
		else:
			function=foundFunctions.get(name)
			if function==None:
				reason="NOT_FOUND"

		#REF output
		#extern StrCode64Func* StrCode64;
		line="extern "+name+"Func* "+name+";"

		if reason!=None:
			line='//'+line+'//'+reason#tex commented out			

		outLines.append(line)
		#print(line)		
	return outLines

def BuildAddressMap():
	outLines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		note=entry.get("note")
		reason=None
		address=""
		invalid=False
		if noAddress!=None:
			reason=noAddress
		else:
			function=foundFunctions.get(name)
			#print("function:"+str(function))
			if function==None:
				reason="NOT_FOUND"
			else:
				address="0x"+str(function.getEntryPoint())
		if note==None or lang!="en":#GOTCHA: only on en, see comment about notes in ExportInfo.py
			note=""
		else:
			note="//"+note

		if reason!=None:
			address=reason

		#address map
		#REF output
		#{"StrCode64", 0x14c1bd730},
		line='{"'+name+'", '+address+'},'+note
		if reason!=None:
			line="//"+line
		outLines.append(line)
		#print(line)
	return outLines

def BuildFuncPtrDefs():
	outLines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		reason=None
		if noAddress!=None:
			reason=noAddress
		else:
			function=foundFunctions.get(name)
			#print("function:"+str(function))
			if function==None:
				reason="NOT_FOUND"

		#REF output
		#StrCode64Func* StrCode64;
		line=name+'Func* '+name+';'
		if reason!=None:
			line='//'+line+'//'+reason

		outLines.append(line)
		#print(line)
	return outLines

def BuildFuncPtrSet():
	outLines=[]
	for entry in exportInfo:
		name=entry["name"]
		#print(name)
		noAddress=entry.get("noAddress")
		reason=None
		if noAddress!=None:
			reason=noAddress
		else:
			function=foundFunctions.get(name)
			#print("function:"+str(function))
			if function==None:
				reason="NOT_FOUND"

		#REF output
		#StrCode64 = (StrCode64Func*)addressSet["StrCode64"];
		line=name+' = ('+name+'Func*)addressSet["'+name+'"];'
		if reason!=None:
			line='//'+line+'//'+reason

		outLines.append(line)
		#print(line)
	return outLines


#REF
#typedef foxlua::module * (__fastcall NewModuleFunc)(undefined8 param_1, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
# REF output
# foxlua::module* NewModuleFuncHook(undefined8 param_1, const char* moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
#
# 	return NewModule(param_1, moduleName, param_3, param_4, param_5);
# }
def BuildHookFuncStubs():
	print('BuildHookFuncStubs')
	signatureLines=[]

	for entry in exportInfo:
		name=entry["name"]

		noAddress=entry.get("noAddress")
		exportFunc=entry.get("exportFunc")
		address=""
		invalidReason=None
		signatureLine=""
		if noAddress!=None:
			invalidReason=noAddress
		elif exportFunc==False:
			invalidReason="EXPORT_FUNC_FALSE"
		else:
			function=foundFunctions.get(name)
			if function==None:
				invalidReason="NOT_FOUND"
			else:
				address=""
				#print(function.getName())
				signature=function.getSignature()
				#print(signature.getPrototypeString())
				returnType=signature.getReturnType().getName()
				arguments=signature.getArguments()
				callConvention=signature.getGenericCallingConvention().getDeclarationName() #ZIP: Added calling convention support
				if callConvention=="":
						callConvention="__fastcall"

				#REF foxlua::module* NewModuleFuncHook(undefined8 param_1, const char* moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
				#tex TODO: probably don't need to worry about matching call convention for our own functions, let the compiler do what its supposed to, maybe thiscalls though?
				#signatureLine=callConvention + " " + returnType+" "+name+"Hook"+"("	
				signatureLine=returnType+" "+name+"Hook"+"("	
				#WORKAROUND: tex ghidra signature doesnt have const keyword
				constCharPtr=entry.get("constCharPtr")#tex currently will apply const to char * by default, or constCharPtr:False to skip TODO: don't know which is the most common/to have as default. in general you use const char* for string literals and char* for buffers/actual mutable strings
				constParams=entry.get("constParams")#WORKAROUND: per param const declaration
				for idx,parameter in enumerate(arguments):
					paramName=parameter.getName()
					dataTypeName=parameter.getDataType().getName()
					#print(paramName)
					#print(dataTypeName)
					if callConvention=="__thiscall" and paramName=="this":
						paramName="This"#WORKAROUND ZIP: Fixes "this" param in __thiscall
					if constCharPtr!=False:
						if dataTypeName=="char *":
							dataTypeName="const "+dataTypeName
					if constParams!=None:
						for constParam in constParams:
							#print(constParam)
							if constParam==paramName:
								dataTypeName="const "+dataTypeName
								break
					signatureLine=signatureLine+dataTypeName+" "+paramName
					if idx!=len(arguments)-1:
						signatureLine=signatureLine+", "
				if function.hasVarArgs()==True:
					signatureLine=signatureLine+", ..."
				signatureLine=signatureLine+") {"
				signatureLines.append(signatureLine)#line
				signatureLines.append("")#line
				#REF	return NewModule(param_1, moduleName, param_3, param_4, param_5);
				if returnType=="void":
					returnLine="\t"+name+"("
				else:
					returnLine="\t"+"return "+name+"("
				for idx,parameter in enumerate(arguments):
					paramName=parameter.getName()
					returnLine=returnLine+paramName
					if idx!=len(arguments)-1:
						returnLine=returnLine+", "	
				returnLine=returnLine+");"
				signatureLines.append(returnLine)#line
				signatureLines.append("}//"+name+"Hook")#line
				signatureLines.append("")#line
		if invalidReason!=None:
			signatureLine="// "+name+" "+invalidReason
			signatureLines.append(signatureLine)

		#debugprint('signatureLine:'+signatureLine)
	return signatureLines

def WriteAddressHFile():
	fileName=exeName+"_adresses_"+version+"_"+lang
	headerFilePath=hDestPath+fileName+".h"

	addressLines=BuildAddressMap()

	header=[
		"#pragma once",
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteAddressHFile",
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	hLines=[]

	for line in header:
		hLines.append(line)

	hLines.append("")
	hLines.append("#include <map>")
	hLines.append("")

	hLines.append("namespace IHHook {")
	indent="\t"
	hLines.append(indent+"std::map<std::string, int64_t> "+fileName+"{")

	indent="\t\t"
	for line in addressLines:
		hLines.append(indent+line)

	indent="\t"
	hLines.append(indent+"};//map "+fileName)
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
		"//via WriteFuncTypeDefHFile",
		"//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)",
	]

	includes=[	
		'#include "mgsvtpp_func_typedefs_manual.h"',
		'//TODO: this is a per category thing/will likely want to manage includes ',
		'//as the number of functions being hooked with various data types expands',
		'#include "lua/lua.h"',
		'#include "lua/lauxlib.h"',
	]

	file = PrintWriter(headerFilePath);
	for line in header:
		file.println(line)
	file.println("")
	for line in includes:
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

def WriteFuncPtrDefsFile():
	fileName=exeName+"_funcptr_defs"+".cpp"
	headerFilePath=hDestPath+fileName

	funcPtrLines=BuildFuncPtrDefs()

	header=[
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteFuncPtrDefsFile",
		"//declares function pointers of exported functions",
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	hLines=[]

	for line in header:
		hLines.append(line)
	hLines.append("")
	hLines.append('#include "mgsvtpp_func_typedefs.h"',)
	hLines.append("")

	indent=""
	for line in funcPtrLines:
		hLines.append(indent+line)

	file = PrintWriter(headerFilePath);
	for line in hLines:
		file.println(indent+line)
		print(line)

	file.flush()
	file.close()

def WriteFuncPtrSetFile():
	fileName=exeName+"_funcptr_set"+".cpp"
	headerFilePath=hDestPath+fileName

	funcPtrLines=BuildFuncPtrSet()

	header=[
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteFuncPtrSetFile",
		"//function for setting function pointers of exported functions.",
		"//addresses in addressset should be rebased or found by sig scan before this is called"
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	hLines=[]

	for line in header:
		hLines.append(line)
	hLines.append("")
	hLines.append('#include "mgsvtpp_func_typedefs.h"',)

	hLines.append("")
	hLines.append("extern std::map<std::string, int64_t> addressSet;")
	hLines.append("")
	hLines.append("namespace IHHook {")
	indent="\t"

	hLines.append(indent+"void SetFuncPtrs() {")
	indent="\t\t"
	for line in funcPtrLines:
		hLines.append(indent+line)
	indent="\t"
	hLines.append(indent+"}//SetFuncPtrs")

	hLines.append("")

	indent=""
	hLines.append(indent+"}//namespace IHHook")

	file = PrintWriter(headerFilePath);
	for line in hLines:
		file.println(indent+line)
		print(line)

	file.flush()
	file.close()

def WriteHookStubsFile():
	fileName=exeName+"_hook_stubs"+".cpp"
	headerFilePath=hDestPath+fileName

	stubLines=BuildHookFuncStubs()

	header=[
		"//" + fileName,
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteHookStubsFile",
		"//Not intended to be compiled, this is just stub/examples of hook functions", 
		"//so you can quickly just copy and paste them to get started.",
	]

	hLines=[]

	for line in header:
		hLines.append(line)
	hLines.append("")

	hLines.append("namespace IHHook {")
	indent="\t"

	for line in stubLines:
		hLines.append(indent+line)

	hLines.append("")

	indent=""
	hLines.append(indent+"}//namespace IHHook")

	file = PrintWriter(headerFilePath);
	for line in hLines:
		file.println(indent+line)
		print(line)

	file.flush()
	file.close()

#exec
lang = askChoice("ExportHooksToHeader", "Select lang of this exe:", ["en","jp"], "en")

print("----")
WriteAddressHFile()
print("----")
WriteFuncTypeDefHFile()
print("----")
WriteFuncPtrDefsFile()
print("----")
WriteFuncPtrSetFile()
print("----")
WriteHookStubsFile()

