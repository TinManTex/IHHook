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

#SYNC these settings with user file ExportSettings_User
#tex rather than editing these a user should copy ExportPath_User.py to ghidra program folder and edit path.
hDestPath='D:/GitHub/IHHook/'#tex should be to repo root, 
hDestSubPath='IHHook/hooks/'#tex only should be changed if the ihhook project changes the location

version="1_0_15_3"
exeName="mgsvtpp"

debugmode=False #enables debugprints

#except any of the above can be overridden by ExportPath_User.py
#Don't need to change any settings past here
hUserFile='./ExportSettings_User.py'

print('hDestPath: initial ' + hDestPath)

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
#tex nice idea in theory, but so far it's better to analyse the outputted files than scroll through a log window
def debugprint(*args):
	if debugmode:
		print(args)

#tex there's bound to be this functionailty somewhere in ghidra api, probably somewhere with SymbolPaths
def GetNameSpacePathFromSymbol(symbol):
	namespacePath=''
	parent=symbol.getParentNamespace()
	while parent.getName()!='Global':
		if namespacePath=='':
			namespacePath=parent.getName()
		else:
			namespacePath=parent.getName()+'::'+namespacePath
		
		parent=parent.getParentNamespace()
	return namespacePath

def GetNamespaceListFromName(name):
	namespacesList=name.split('::')
	functionName=namespacesList.pop()#tex just want the namespaces, not func name
	isNamespaced=len(namespacesList)>0
	return namespacesList,functionName,isNamespaced

def GetFunctionName(name):
	return name.split('::').pop()#tex a split of string with no matches is a list of string. pop will get last in list, which in either case will be function name

def GetNameSpacePathFromName(name):
	functionName=name
	namespaces=''
	pos=name.rfind('::')#tex find last
	if pos!=-1:
		namespaces=name[0:pos]
		functionName=name[pos+2:]#tex +2 for '::'.
	return namespaces,functionName
	

#tex using exportInfo to give order,
# while list[{dict of name:name, other info}] is a bit of a pain rather than dict{name:{dict of info}} 
# i didnt want to dic(t) around with OrderedDict (and ghidra uses jython/python 2.7 which dicts dont have insertion order)
infoLookup={}
for idx, entry in enumerate(exportInfo):
	infoLookup[entry["name"]]=idx

#test#for name in infoLookup:
	#print(name)

def getinfo(name):
	idx=infoLookup.get(name)
	if idx==None:
		return None
	else:
		return exportInfo[idx]

#test#print(getinfo("luaopen_string"))

numFound=0
listing = currentProgram.getListing()

#tex old/fallback if not giving namespace in ExportInfo
print("building foundFunctions")
foundFunctions={
	#[exportInfo name]=function
}
#CULL old
# for function in listing.getFunctions(True):
# 	if not function.isThunk():
# 		if getinfo(function.getName())!=None:
# 			#test#print("found " + function.getName())			
# 			#print("parent namespace:" + function.getParentNamespace().getName())
# 			foundFunctions[function.getName()]=function


#tex find by namespace (or Global)
#overwrites previous
for idx,entry in enumerate(exportInfo):
	if entry.get("noAddress")==None:
		name=entry['name']#tex qualified name (assuming its namespaced)
		namespaces,functionName=GetNameSpacePathFromName(name)
		#debugprint('GetNameSpacePathFromName('+name+')="'+namespaces+'","'+functionName+'"')
		if namespaces=='':#tex fallback, will only hit if not actually in a namespace
			namespaces='Global'
		namespaceFunctions=listing.getFunctions(namespaces,functionName)
		#print('namespaceFunctions:',namespaceFunctions)

		if len(namespaceFunctions)==0:
			print('WARNING:'+entry['name']+': no functions found for namespace "'+namespaces+'"')
			print('Using much slower fallback to find functions. please add or correct namespaces on ExportInfo name entry')
			#tex fallback to finding in whole listing
			#a lot slower than old method of just iterating listing once, but this will warn if theres multiple of same name
			#but this exec path shouldnt even be hit, once exportInfo names are properly namespaced
			#and functions in ghidra not yet namespaced will have bypassed this due to being in Global
			#print(entry['name'] + ': no functions of that name found for namespace ' + namespaces)
			namespaceFunctions=[]
			namespaces="UNKNOWN"
			for function in listing.getFunctions(True):
				if not function.isThunk():
					if function.getName()==functionName:
						print("fallback found " + function.getName())			
						#print("parent namespace:" + function.getParentNamespace().getName())
						namespaces=GetNameSpacePathFromSymbol(function)
						print("namespaces on found function:'"+namespaces+"'")#DEBUG
						namespaceFunctions.append(function)
		
		namespaceFunctions = [func for func in namespaceFunctions if not func.isThunk()]#tex new list without thunks

		numFunctions=len(namespaceFunctions)
		if numFunctions==0:
			print(entry['name']+': no functions of that name found for namespace '+namespaces)
		elif numFunctions > 1:
			print('WARNING:'+entry['name']+': multiple functions found for namespace '+namespaces)
			for func in namespaceFunctions:
				address="0x"+str(function.getEntryPoint())
				print(address)

			function=namespaceFunctions[0]
			foundFunctions[entry['name']]=function
		else:
			function=namespaceFunctions[0]
			foundFunctions[entry['name']]=function

		debugprint(entry['name']+" namespaces:'"+namespaces+"' name:'"+functionName+"'")
		debugprint('namespaceFunctions:',namespaceFunctions)

#tex DEBUG
debugprint("foundFunctions:")
for key in foundFunctions:
	debugprint(key, '->', foundFunctions[key])



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
				returnType=signature.getReturnType().getName()
				arguments=signature.getArguments()

				namespacesList,functionName,isNamespaced=GetNamespaceListFromName(name)

				namespaceOpenLine=''
				namespaceCloseLine=''
				for namespace in namespacesList:
					namespaceOpenLine='namespace '+namespace+'{'+namespaceOpenLine #tex just jam them on one line, this is a generated file
					namespaceCloseLine='}'+namespaceCloseLine
				
				signatureLine=returnType+" "+name
				#REF typeDefLine: 
				# typedef foxlua::module * (__fastcall NewModuleFunc)(undefined8 param_1, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
				callConvention=signature.getGenericCallingConvention().getDeclarationName() #ZIP: Added calling convention support
				if callConvention=="":
						callConvention="__fastcall"
				typedefLine="typedef "+returnType+" ("+callConvention+" "+GetFunctionName(name)+"Func)("
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

				if isNamespaced:
					typedefLines.append(namespaceOpenLine)
				typedefLines.append(typedefLine)
				if isNamespaced:
					typedefLines.append(namespaceCloseLine)
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
		
		namespacesList,functionName,isNamespaced=GetNamespaceListFromName(name)
		namespaceOpenLine=''
		namespaceCloseLine=''
		for namespace in namespacesList:
			namespaceOpenLine='namespace '+namespace+'{'+namespaceOpenLine #tex just jam them on one line, this is a generated file
			namespaceCloseLine='}'+namespaceCloseLine	

		if isNamespaced:
			outLines.append(namespaceOpenLine)

		#REF output
		#extern StrCode64Func* StrCode64;
		line="extern "+GetFunctionName(name)+"Func* "+GetFunctionName(name)+";"

		if reason!=None:
			line='//'+line+'//'+reason#tex commented out			

		outLines.append(line)

		if isNamespaced:
			outLines.append(namespaceCloseLine)
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
		#GetStrCodeWithLengthFunc = (GetStrCodeWithLengthFunc*)addressSet["GetStrCodeWithLengthFunc"];
		line=name+' = ('+name+'Func*)addressSet["'+name+'"];'
		if reason!=None:
			line='//'+line+'//'+reason
		outLines.append(line)
		#print(line)

		#REF
		#funcPtrPtrs["GetStrCodeWithLength"] = &GetStrCodeWithLength;
		line='funcPtrPtrs["'+name+'"] = &'+name+';'
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
		if entry.get("usingHook") != True:
			continue

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
				signatureLine=returnType+" "+GetFunctionName(name)+"Hook"+"("	
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
				signatureLines.append("}//"+GetFunctionName(name)+"Hook")#line
				signatureLines.append("")#line
		if invalidReason!=None:
			signatureLine="// "+name+" "+invalidReason
			signatureLines.append(signatureLine)

		#debugprint('signatureLine:'+signatureLine)
	return signatureLines

def BuildHookCreatHookExamples():
	print('BuildHookFuncStubs')
	outputLines=[]

	for entry in exportInfo:
		if entry.get("usingHook") != True:
			continue

		name=entry["name"]

		noAddress=entry.get("noAddress")
		exportFunc=entry.get("exportFunc")
		invalidReason=None
		if noAddress!=None:
			invalidReason=noAddress
		elif exportFunc==False:
			invalidReason="EXPORT_FUNC_FALSE"
		else:
			function=foundFunctions.get(name)
			if function==None:
				invalidReason="NOT_FOUND"
			else:
				#REF 				
				# CREATEHOOK(foxlua::NewModule, NewModuleHook)
				# ENABLEHOOK(foxlua::NewSubModule)
				outputLines.append("CREATEHOOK("+name+","+GetFunctionName(name)+"Hook)")
				outputLines.append("ENABLEHOOK("+name+")")
				outputLines.append("")


		if invalidReason!=None:
			outputLines.append("// "+name+" "+invalidReason)

	return outputLines

def WriteAddressHFile():
	print(__name__)
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
	hLines.append(indent+"std::map<std::string, uint64_t> "+fileName+"{")

	indent="\t\t"
	for line in addressLines:
		hLines.append(indent+line)

	indent="\t"
	hLines.append(indent+"};//map "+fileName)
	hLines.append("}//namespace IHHook")

	file = PrintWriter(headerFilePath)
	for line in hLines:
		file.println(line)
		debugprint(line)

	file.flush()
	file.close()

def WriteFuncTypeDefHFile():
	print(__name__)
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

	footer=[
		"//tex WORKAROUND: lua usually isnt in a namespace, so just push it so dont have to futz with it for any existing code",
		"//shift this out if you ever break up mgsvtpp_func_typedefs",
		"using namespace lua;",
	]

	file = PrintWriter(headerFilePath)
	for line in header:
		file.println(line)
	file.println("")
	for line in includes:
		file.println(line)
	file.println("")
	for line in signatures:
		file.println(line)
		debugprint(line)
	file.println("")
	file.println("//tex the (extern of the) function pointers")
	for line in externPointersLines:
		file.println(line)
		debugprint(line)
	file.println("")
	for line in footer:
		file.println(line)
	file.println("")

	file.flush()
	file.close()

def WriteFuncPtrDefsFile():
	print(__name__)
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

	file = PrintWriter(headerFilePath)
	for line in hLines:
		file.println(indent+line)
		debugprint(line)

	file.flush()
	file.close()

def WriteFuncPtrSetFile():
	print(__name__)
	fileName=exeName+"_funcptr_set"+".cpp"
	headerFilePath=hDestPath+fileName

	funcPtrLines=BuildFuncPtrSet()

	header=[
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteFuncPtrSetFile",
		"//function for setting function pointers of exported functions.",
		"//addresses in addressSet should be rebased or found by sig scan before this is called"
		"",
		"// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list",
		"// NO_USE - something we dont really want to use for whatever reason",
		"// USING_CODE - using the default lapi code implementation instead of hooking",
	]

	includes=[
		'#include "mgsvtpp_func_typedefs.h"',
		'#include <map>',
		'#include <string>',
		'#include <stdint.h>',
	]

	functionComment="//tex addresses in addressSet should be rebased or found by sig scan before this is called"

	hLines=[]

	for line in header:
		hLines.append(line)
	hLines.append("")

	for line in includes:
		hLines.append(line)
	hLines.append("")

	hLines.append("namespace IHHook {")
	indent="\t"
	hLines.append(indent+"extern std::map<std::string, uint64_t> addressSet;")
	hLines.append(indent+"extern std::map<std::string, void*> funcPtrPtrs;")


	hLines.append(indent+functionComment)
	hLines.append(indent+"void SetFuncPtrs() {")
	indent="\t\t"
	for line in funcPtrLines:
		hLines.append(indent+line)
	indent="\t"
	hLines.append(indent+"}//SetFuncPtrs")

	hLines.append("")

	indent=""
	hLines.append(indent+"}//namespace IHHook")

	file = PrintWriter(headerFilePath)
	for line in hLines:
		file.println(indent+line)
		debugprint(line)

	file.flush()
	file.close()

def WriteHookStubsFile():
	print(__name__)
	fileName=exeName+"_hook_stubs"+".cpp"
	headerFilePath=hDestPath+fileName

	stubLines=BuildHookFuncStubs()
	createHookLines=BuildHookCreatHookExamples()

	header=[
		"//" + fileName,
		"//GENERATED: by ghidra script ExportHooksToHeader.py",
		"//via WriteHookStubsFile",
		"//Not intended to be compiled, this is just stub/examples of hook functions", 
		"//so you can quickly just copy and paste them to get started.",
		"//only generated for ExportInfo entries that have usingHook True"
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

	hLines.append(indent+"void CreateHooks() {")
	indent=indent+"\t"
	for line in createHookLines:
		hLines.append(indent+line)

	hLines.append(indent+"}//CreateHooks")

	indent=""
	hLines.append(indent+"}//namespace IHHook")

	file = PrintWriter(headerFilePath)
	for line in hLines:
		file.println(indent+line)
		debugprint(line)

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

