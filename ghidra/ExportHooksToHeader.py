#TODO write a description for this script
#@author 
#@category Strings
#@keybinding 
#@menupath 
#@toolbar 

#NOTE: make sure the function signature (not to be confused with sig string/pattern) 
#for the function you want to export is correct in ghidra, or at least understandable for IHHook, no data types set as 'undefined'
#then right click the function in decompile window (or press P) and choose 'Commit Params/Return'
#GOTCHA: ghidra signature doesnt have const keyword, so theres some WORKAROUND

from java.io import PrintWriter

hDestPath="D:/GitHub/IHHook/IHHook/"

#KLUDGE uncomment the lang of the exe youre running on and comment out the other
lang="en"
#lang="jp"

version="1_0_15_3"
exeName="mgsvtpp"

#TODO add NO_USE to getllocf,setallocf, actually give reason why not (dont want to mess with allocator function)
#todo namespaces - not actual, just to split into different files
#fox, lua
exportInfo=[
	#{"name":"_mainCRTStartup","note: since its the entry point no point trying hooking since it's already done"},
	#{"name":"FoxMain","note: since its the entry point no point trying hooking since it's already done"},
	{"name":"StrCode64",},
	{"name":"FNVHash32",},
	#{"name":"FNVHash64",},
	{"name":"GetFreeRoamLangId",},
	{"name":"UpdateFOVLerp","note":"TODO: verify the return AL>RAX"},
	{"name":"UnkSomePrintFunction","note":"Some info printing function that has been stubbed out"},
	{"name":"l_StubbedOut",},
	#{"name":"UnkSomePlayerUpdateFunc","note":"exploration"},
	#{"name":"UnkAnotherPlayerUpdateFuncButHuge","note":"exploration"},
	{"name":"nullsub_2"},
	{"name":"LoadFile"},
	#<
	#lua>
	{"name":"lua_newstate","note":"tex could use default implementation, but may want to hook if we want to see what the engine is up to"},
	{"name":"lua_close",},
	{"name":"lua_newthread",},

	{"name":"lua_atpanic",},

	{"name":"lua_gettop", "noAddress":"USING_CODE",},
	{"name":"lua_settop",},
	{"name":"lua_pushvalue",},
	{"name":"lua_remove",},
	{"name":"lua_insert",},
	{"name":"lua_replace",},
	{"name":"lua_checkstack",},
	{"name":"lua_xmove",},

	{"name":"lua_isnumber",},
	{"name":"lua_isstring",},
	{"name":"lua_iscfunction",},
	{"name":"lua_isuserdata", "noAddress":"USING_CODE",},
	{"name":"lua_type",},
	{"name":"lua_typename", "noAddress":"USING_CODE",},

	{"name":"lua_equal", "note":"tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation" },
	{"name":"lua_rawequal",},
	{"name":"lua_lessthan",},
	{"name":"lua_tonumber",},
	{"name":"lua_tointeger",},
	{"name":"lua_toboolean",},
	{"name":"lua_tolstring",},
	{"name":"lua_objlen",},
	{"name":"lua_tocfunction",},
	{"name":"lua_touserdata",},
	{"name":"lua_tothread",},
	{"name":"lua_topointer",},

	{"name":"lua_pushnil",},
	{"name":"lua_pushnumber",},
	{"name":"lua_pushinteger",},
	{"name":"lua_pushlstring",},
	{"name":"lua_pushstring",},
	{"name":"lua_pushvfstring",},
	{"name":"lua_pushfstring",},
	{"name":"lua_pushcclosure",},
	{"name":"lua_pushboolean",},
	{"name":"lua_pushlightuserdata",},
	{"name":"lua_pushthread",},

	{"name":"lua_gettable",},
	{"name":"lua_getfield",},
	{"name":"lua_rawget",},
	{"name":"lua_rawgeti","note":"via MACRO lua_getref",},
	{"name":"lua_createtable",},
	{"name":"lua_newuserdata",},
	{"name":"lua_getmetatable",},
	{"name":"lua_getfenv",},

	{"name":"lua_settable",},
	{"name":"lua_setfield",},
	{"name":"lua_rawset",},
	{"name":"lua_rawseti",},
	{"name":"lua_setmetatable",},
	{"name":"lua_setfenv",},

	{"name":"lua_call",},
	{"name":"lua_pcall",},
	{"name":"lua_cpcall",},
	{"name":"lua_load",},

	{"name":"lua_dump",},

	{"name":"lua_yield", "noAddress":"USING_CODE",},
	{"name":"lua_resume",},
	{"name":"lua_status", "noAddress":"USING_CODE", "note":"tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)",},

	{"name":"lua_gc",},
	{"name":"lua_error",},

	{"name":"lua_next",},
	{"name":"lua_concat",},

	{"name":"lua_getallocf", "noAddress":"NO_USE","note":"tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation" },
	{"name":"lua_setallocf", "noAddress":"NO_USE","note":"tex don't really want to mess with allocator function anyway"},


	{"name":"lua_setlevel", "noAddress":"NO_USE","note":"tex: labeled by lua as a hack to be removed in lua 5.2",},

	{"name":"lua_getstack",},
	{"name":"lua_getinfo",},
	{"name":"lua_getlocal",},
	{"name":"lua_setlocal",},
	{"name":"lua_getupvalue",},
	{"name":"lua_setupvalue",},

	{"name":"lua_sethook",},
	{"name":"lua_gethook", "noAddress":"USING_CODE",},
	{"name":"lua_gethookmask", "noAddress":"USING_CODE",},
	{"name":"lua_gethookcount", "noAddress":"USING_CODE",},
	#lua<

	#lauxlib.h>
	{"name":"luaI_openlib", "constParams": ["l"]},
	{"name":"luaL_register", "noAddress":"USING_CODE",},
	{"name":"luaL_getmetafield",},
	{"name":"luaL_callmeta",},
	{"name":"luaL_typerror",},
	{"name":"luaL_argerror",},
	{"name":"luaL_checklstring",},
	{"name":"luaL_optlstring",},
	{"name":"luaL_checknumber",},
	{"name":"luaL_optnumber", "noAddress":"USING_CODE",},

	{"name":"luaL_checkinteger",},
	{"name":"luaL_optinteger",},

	{"name":"luaL_checkstack",},
	{"name":"luaL_checktype",},
	{"name":"luaL_checkany",},

	{"name":"luaL_newmetatable",},
	{"name":"luaL_checkudata",},

	{"name":"luaL_where",},
	{"name":"luaL_error",},

	{"name":"luaL_checkoption",},

	{"name":"luaL_ref", "noAddress":"USING_CODE", "note":"tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info",},
	{"name":"luaL_unref", "noAddress":"USING_CODE",},

	{"name":"luaL_loadfile",},
	{"name":"luaL_loadbuffer",},
	{"name":"luaL_loadstring", "noAddress":"USING_CODE",},

	{"name":"luaL_newstate",},

	{"name":"luaL_gsub",},

	{"name":"luaL_findtable",},
	#...
	{"name":"luaL_buffinit", "noAddress":"USING_CODE",},
	{"name":"luaL_prepbuffer",},
	{"name":"luaL_addlstring",},
	{"name":"luaL_addstring", "noAddress":"USING_CODE",},
	{"name":"luaL_addvalue",},
	{"name":"luaL_pushresult",},
	#lauxlib.h<

	#luaLib.h>
	{"name":"luaopen_base",},
	{"name":"luaopen_table",},
	{"name":"luaopen_io",},
	{"name":"luaopen_os",},
	{"name":"luaopen_string",},
	{"name":"luaopen_math",},
	{"name":"luaopen_debug",},
	{"name":"luaopen_package",},
	{"name":"luaL_openlibs",},
	#luaLib.h<
]#exportInfo

#Don't need to change anything past here

#tex using list above to give order
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

def BuildExternAddr():
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

		externLine="extern intptr_t * "+name+"Addr;"

		if invalidReason!=None:
			lines.append("//"+externLine+"//"+invalidReason)
		else:
			lines.append(externLine)
	return lines


#tex existing/adapted AddressCSVToMacroHeader
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
	externAddrLines=BuildExternAddr()

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
	file.println("//tex for want of a better place, used by ENABLE/DISABLEHOOK")
	for line in externAddrLines:
		file.println(line)
		print(line)

	file.flush()
	file.close()

print("----")
WriteAddressHFile()
print("----")
WriteFuncTypeDefHFile()

