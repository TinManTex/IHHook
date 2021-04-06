#pragma once
#include "../HookMacros.h"

FUNC_DECL_SIG(lua_newstate, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\x4C\x89\x00\x48\x89\x00\x41\xB9", 
	"xx???xx???xx???xxxx?xx?xx?xx?xx")
FUNC_DECL_PATTERN(lua_newstate, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 89 ? 4C 89 ? 48 89 ? 41 B9")

FUNC_DECL_SIG(lua_close, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x8B\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x89\x00\x48\x8B\x00\x00\xE8", 
	"xx???xxxx?xx??xx?????xx?xx??x")
FUNC_DECL_PATTERN(lua_close, "48 89 ? ? ? 57 48 83 EC ? 48 8B ? ? 48 8B ? ? ? ? ? 48 89 ? 48 8B ? ? E8")

FUNC_DECL_SIG(lua_newthread, 
	"\x53\x48\x83\xEC\x00\x48\x8B\x00\x00\x48\x89\x00\x48\x8B\x00\x00\x48\x39\x00\x00\x00\x00\x00\x72", 
	"xxxx?xx??xx?xx??xx?????x")
FUNC_DECL_PATTERN(lua_newthread, "53 48 83 EC ? 48 8B ? ? 48 89 ? 48 8B ? ? 48 39 ? ? ? ? ? 72")

FUNC_DECL_SIG(lua_atpanic, 
	"\x4C\x8B\x00\x00\x49\x8B\x00\x00\x00\x00\x00\x49\x89\x00\x00\x00\x00\x00\xC3", 
	"xx??xx?????xx?????x")
FUNC_DECL_PATTERN(lua_atpanic, "4C 8B ? ? 49 8B ? ? ? ? ? 49 89 ? ? ? ? ? C3")

//FUNC_DECL_SIG(lua_gettop, USING_CODE)

FUNC_DECL_SIG(lua_settop, 
	"\x85\xD2\x78\x00\x4C\x63\x00\x48\x8B", 
	"xxx?xx?xx")
FUNC_DECL_PATTERN(lua_settop, "85 D2 78 ? 4C 63 ? 48 8B")

FUNC_DECL_SIG(lua_pushvalue,
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x4D\x8B\x00\x00\x48\x8B", 
	"xxx?xx?x????xx??xx")
FUNC_DECL_PATTERN(lua_pushvalue, "48 83 EC ? 49 89 ? E8 ? ? ? ? 4D 8B ? ? 48 8B")

FUNC_DECL_SIG(lua_remove, 
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x48\x83\xC0", 
	"xxx?xx?x????xxx")
FUNC_DECL_PATTERN(lua_remove, "48 83 EC ? 49 89 ? E8 ? ? ? ? 48 83 C0")

FUNC_DECL_SIG(lua_insert, 
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x49\x8B\x00\x00\x49\x89", 
	"xxx?xx?x????xx??xx")
FUNC_DECL_PATTERN(lua_insert, "48 83 EC ? 49 89 ? E8 ? ? ? ? 49 8B ? ? 49 89")

FUNC_DECL_SIG(lua_replace,
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x89\xD7\x48\x89\x00\x81\xFA\x00\x00\x00\x00\x75", 
	"xx???xxxx?xxxx?xx????x")
FUNC_DECL_PATTERN(lua_replace, "48 89 ? ? ? 57 48 83 EC ? 89 D7 48 89 ? 81 FA ? ? ? ? 75")

FUNC_DECL_SIG(lua_checkstack, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\x81\xFA", 
	"xx???xxxx?xx?xx")
FUNC_DECL_PATTERN(lua_checkstack, "48 89 ? ? ? 57 48 83 EC ? 48 89 ? 81 FA")

FUNC_DECL_SIG(lua_xmove, 
	"\x49\x89\x00\x49\x89\x00\x48\x39\x00\x74\x00\x4D\x63", 
	"xx?xx?xx?x?xx")
FUNC_DECL_PATTERN(lua_xmove, "49 89 ? 49 89 ? 48 39 ? 74 ? 4D 63")

FUNC_DECL_SIG(lua_isnumber, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x74\x00\x48\x8D\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x85\x00\x75\x00\x48\x83\xC4\x00\xC3\xB8", 
	"xxx?x????xxx?x?xx???xx?x????xx?x?xxx?xx")
FUNC_DECL_PATTERN(lua_isnumber, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 74 ? 48 8D ? ? ? 48 89 ? E8 ? ? ? ? 48 85 ? 75 ? 48 83 C4 ? C3 B8")

FUNC_DECL_SIG(lua_isstring, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x39\x00\x74", 
	"xxx?x????xx?????xx?x")
FUNC_DECL_PATTERN(lua_isstring, "48 83 EC ? E8 ? ? ? ? 48 8D ? ? ? ? ? 48 39 ? 74")

FUNC_DECL_SIG(lua_iscfunction, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x75\x00\x48\x8B\x00\x80\x78\x0A\x00\x74\x00\xB8", 
	"xxx?x????xxx?x?xx?xxx?x?x")
FUNC_DECL_PATTERN(lua_iscfunction, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 75 ? 48 8B ? 80 78 0A ? 74 ? B8")

//FUNC_DECL_SIG(lua_isuserdata, USING_CODE)

FUNC_DECL_SIG(lua_type, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x39\x00\x75", 
	"xxx?x????xx?????xx?x")
FUNC_DECL_PATTERN(lua_type, "48 83 EC ? E8 ? ? ? ? 48 8D ? ? ? ? ? 48 39 ? 75")

//FUNC_DECL_PATTERN(lua_typename, USING_CODE)

//FUNC_DECL_SIG(lua_equal, NOT_FOUND)//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation

FUNC_DECL_SIG(lua_rawequal, 
	"\x53\x48\x83\xEC\x00\x45\x89\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x44\x89\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x39\x00\x74\x00\x48\x39\x00\x74\x00\x48\x89", 
	"xxxx?xx?xx?x????xx?xx?xx?x????xx?????xx?x?xx?x?xx")
FUNC_DECL_PATTERN(lua_rawequal, "53 48 83 EC ? 45 89 ? 49 89 ? E8 ? ? ? ? 44 89 ? 4C 89 ? 48 89 ? E8 ? ? ? ? 48 8D ? ? ? ? ? 48 39 ? 74 ? 48 39 ? 74 ? 48 89")

FUNC_DECL_SIG(lua_lessthan, 
	"\x53\x48\x83\xEC\x00\x45\x89\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x44\x89\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x39\x00\x74\x00\x48\x39\x00\x74\x00\x49\x89", 
	"xxxx?xx?xx?x????xx?xx?xx?x????xx?????xx?x?xx?x?xx")
FUNC_DECL_PATTERN(lua_lessthan, "53 48 83 EC ? 45 89 ? 49 89 ? E8 ? ? ? ? 44 89 ? 4C 89 ? 48 89 ? E8 ? ? ? ? 48 8D ? ? ? ? ? 48 39 ? 74 ? 48 39 ? 74 ? 49 89")

FUNC_DECL_SIG(lua_tonumber, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x74\x00\x48\x8D\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x85\x00\x75\x00\x0F\x57", 
	"xxx?x????xxx?x?xx???xx?x????xx?x?xx")
FUNC_DECL_PATTERN(lua_tonumber, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 74 ? 48 8D ? ? ? 48 89 ? E8 ? ? ? ? 48 85 ? 75 ? 0F 57")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_tointeger, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x74\x00\x48\x8D\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x85\x00\x75\x00\x48\x83\xC4\x00\xC3\xF2\x48", 
	"xxx?x????xxx?x?xx???xx?x????xx?x?xxx?xxx")
FUNC_DECL_PATTERN(lua_tointeger, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 74 ? 48 8D ? ? ? 48 89 ? E8 ? ? ? ? 48 85 ? 75 ? 48 83 C4 ? C3 F2 48")

FUNC_DECL_SIG(lua_toboolean, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x8B\x48\x00\x85\xC9", 
	"xxx?x????xx?xx")
FUNC_DECL_PATTERN(lua_toboolean, "48 83 EC ? E8 ? ? ? ? 8B 48 ? 85 C9")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_tolstring, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x89\xD6\x48\x89\x00\xE8\x00\x00\x00\x00\x49\x89\x00\x83\x78\x08\x00\x74\x00\x48\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x85\xC0\x75\x00\x48\x85", 
	"xx???xx???xxxx?xx?xxxx?x????xx?xxx?x?xx?xx?x????xxx?xx")
FUNC_DECL_PATTERN(lua_tolstring, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 89 D6 48 89 ? E8 ? ? ? ? 49 89 ? 83 78 08 ? 74 ? 48 89 ? 48 89 ? E8 ? ? ? ? 85 C0 75 ? 48 85")

FUNC_DECL_SIG(lua_objlen, 
	"\x53\x48\x83\xEC\x00\x49\x89\x00\xE8", 
	"xxxx?xx?x")
FUNC_DECL_PATTERN(lua_objlen, "53 48 83 EC ? 49 89 ? E8")

FUNC_DECL_SIG(lua_tocfunction, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x75\x00\x48\x8B\x00\x80\x78\x0A\x00\x74\x00\x48\x8B", 
	"xxx?x????xxx?x?xx?xxx?x?xx")
FUNC_DECL_PATTERN(lua_tocfunction, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 75 ? 48 8B ? 80 78 0A ? 74 ? 48 8B")

FUNC_DECL_SIG(lua_touserdata, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x8B\x48\x00\x83\xF9\x00\x74\x00\x83\xF9\x00\x74\x00\x31\xC0\x48\x83\xC4\x00\xC3\x48\x8B", 
	"xxx?x????xx?xx?x?xx?x?xxxxx?xxx")
FUNC_DECL_PATTERN(lua_touserdata, "48 83 EC ? E8 ? ? ? ? 8B 48 ? 83 F9 ? 74 ? 83 F9 ? 74 ? 31 C0 48 83 C4 ? C3 48 8B")

FUNC_DECL_SIG(lua_tothread, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x83\x78\x08\x00\x74\x00\x31\xC0", 
	"xxx?x????xxx?x?xx")
FUNC_DECL_PATTERN(lua_tothread, "48 83 EC ? E8 ? ? ? ? 83 78 08 ? 74 ? 31 C0")

FUNC_DECL_SIG(lua_topointer, 
	"\x48\x83\xEC\x00\x41\x89\x00\x49\x89\x00\xE8", 
	"xxx?xx?xx?x")
FUNC_DECL_PATTERN(lua_topointer, "48 83 EC ? 41 89 ? 49 89 ? E8")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_pushnil, 
	"\x48\x8B\x00\x00\xC7\x40\x08\x00\x00\x00\x00\x48\x83\x41\x10", 
	"xx??xxx????xxxx")
FUNC_DECL_PATTERN(lua_pushnil, "48 8B ? ? C7 40 08 ? ? ? ? 48 83 41 10")

FUNC_DECL_SIG(lua_pushnumber, 
	"\x48\x8B\x00\x00\xF2\x0F\x00\x00\xC7\x40\x08", 
	"xx??xx??xxx")
FUNC_DECL_PATTERN(lua_pushnumber, "48 8B ? ? F2 0F ? ? C7 40 08")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_pushinteger, 
	"\x48\x8B\x00\x00\x0F\x57\x00\xF2\x48\x00\x00\x00\xC7\x40\x08", 
	"xx??xx?xx???xxx")
FUNC_DECL_PATTERN(lua_pushinteger, "48 8B ? ? 0F 57 ? F2 48 ? ? ? C7 40 08")

FUNC_DECL_SIG(lua_pushlstring, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x8B\x00\x00\x4C\x89", 
	"xx???xx???xx???xxxx?xx??xx")
FUNC_DECL_PATTERN(lua_pushlstring, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 8B ? ? 4C 89")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_pushstring, 
	"\x48\x85\x00\x75\x00\x48\x8B\x00\x00\x89\x50", 
	"xx?x?xx??xx")
FUNC_DECL_PATTERN(lua_pushstring, "48 85 ? 75 ? 48 8B ? ? 89 50")

FUNC_DECL_SIG(lua_pushvfstring, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x8B\x00\x00\x4C\x89\x00\x48\x89\x00\x49\x8B\x00\x00\x48\x89\x00\x49\x39\x00\x00\x00\x00\x00\x72\x00\xE8\x00\x00\x00\x00\x49\x89", 
	"xx???xx???xxxx?xx??xx?xx?xx??xx?xx?????x?x????xx")
FUNC_DECL_PATTERN(lua_pushvfstring, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 8B ? ? 4C 89 ? 48 89 ? 49 8B ? ? 48 89 ? 49 39 ? ? ? ? ? 72 ? E8 ? ? ? ? 49 89")

FUNC_DECL_SIG(lua_pushfstring, 
	"\x48\x89\x00\x00\x00\x4C\x89\x00\x00\x00\x4C\x89\x00\x00\x00\x53\x48\x83\xEC\x00\x4C\x8B", 
	"xx???xx???xx???xxxx?xx")
FUNC_DECL_PATTERN(lua_pushfstring, "48 89 ? ? ? 4C 89 ? ? ? 4C 89 ? ? ? 53 48 83 EC ? 4C 8B")

FUNC_DECL_SIG(lua_pushcclosure, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x8B\x00\x00\x49\x63\x00\x48\x89", 
	"xx???xx???xxxx?xx??xx?xx")
FUNC_DECL_PATTERN(lua_pushcclosure, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 8B ? ? 49 63 ? 48 89")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_pushboolean, 
	"\x4C\x8B\x00\x00\x31\xC0\x85\xD2", "xx??xxxx")
FUNC_DECL_PATTERN(lua_pushboolean, "4C 8B ? ? 31 C0 85 D2")

FUNC_DECL_SIG(lua_pushlightuserdata, 
	"\x48\x8B\x00\x00\x48\x89\x00\xC7\x40\x08\x00\x00\x00\x00\x48\x83\x41\x10", 
	"xx??xx?xxx????xxxx")
FUNC_DECL_PATTERN(lua_pushlightuserdata, "48 8B ? ? 48 89 ? C7 40 08 ? ? ? ? 48 83 41 10")

FUNC_DECL_SIG(lua_pushthread, 
	"\x48\x8B\x00\x00\x48\x89\x00\xC7\x40\x08\x00\x00\x00\x00\x48\x8B\x00\x00\x48\x83\x41\x10", 
	"xx??xx?xxx????xx??xxxx")
FUNC_DECL_PATTERN(lua_pushthread, "48 8B ? ? 48 89 ? C7 40 08 ? ? ? ? 48 8B ? ? 48 83 41 10")

FUNC_DECL_SIG(lua_gettable, 
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x4D\x8B\x00\x00\x49\x83\xC0", 
	"xxx?xx?x????xx??xxx")
FUNC_DECL_PATTERN(lua_gettable, "48 83 EC ? 49 89 ? E8 ? ? ? ? 4D 8B ? ? 49 83 C0")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_getfield, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4D\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89\x00\x49\x83\xC8\x00\x0F\x1F\x00\x00\x49\xFF\x00\x43\x80\x3C\x02\x00\x75\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8B\x00\x00\x4C\x8D\x00\x00\x00\x48\x89", 
	"xx???xxxx?xx?xx?x????xx?xxx?xx??xx?xxxx?x?xx?xx?x????xx??xx???xx")
FUNC_DECL_PATTERN(lua_getfield, "48 89 ? ? ? 57 48 83 EC ? 4D 89 ? 48 89 ? E8 ? ? ? ? 48 89 ? 49 83 C8 ? 0F 1F ? ? 49 FF ? 43 80 3C 02 ? 75 ? 4C 89 ? 48 89 ? E8 ? ? ? ? 4C 8B ? ? 4C 8D ? ? ? 48 89")

FUNC_DECL_SIG(lua_rawget, 
	"\x53\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8B\x00\x00\x48\x8B\x00\x48\x83\xEA", 
	"xxxx?xx?x????xx??xx?xxx")
FUNC_DECL_PATTERN(lua_rawget, "53 48 83 EC ? 48 89 ? E8 ? ? ? ? 48 8B ? ? 48 8B ? 48 83 EA")

//used via MACRO lua_getref
FUNC_DECL_SIG(lua_rawgeti, 
	"\x53\x48\x83\xEC\x00\x45\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8B", 
	"xxxx?xx?xx?x????xx")
FUNC_DECL_PATTERN(lua_rawgeti, "53 48 83 EC ? 45 89 ? 48 89 ? E8 ? ? ? ? 48 8B")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_createtable, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x8B\x00\x00\x44\x89", 
	"xx???xx???xx???xxxx?xx??xx")
FUNC_DECL_PATTERN(lua_createtable, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 8B ? ? 44 89")

FUNC_DECL_SIG(lua_newuserdata, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x8B\x00\x00\x48\x89\x00\x48\x89\x00\x49\x8B\x00\x00\x49\x39", 
	"xx???xxxx?xx??xx?xx?xx??xx")
FUNC_DECL_PATTERN(lua_newuserdata, "48 89 ? ? ? 57 48 83 EC ? 4C 8B ? ? 48 89 ? 48 89 ? 49 8B ? ? 49 39")

FUNC_DECL_SIG(lua_getmetatable, 
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x48\x63", 
	"xxx?xx?x????xx")
FUNC_DECL_PATTERN(lua_getmetatable, "48 83 EC ? 49 89 ? E8 ? ? ? ? 48 63")

FUNC_DECL_SIG(lua_getfenv, 
	"\x48\x83\xEC\x00\x49\x89\x00\xE8\x00\x00\x00\x00\x8B\x48", 
	"xxx?xx?x????xx")
FUNC_DECL_PATTERN(lua_getfenv, "48 83 EC ? 49 89 ? E8 ? ? ? ? 8B 48")

FUNC_DECL_SIG(lua_settable, 
	"\x53\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8B\x00\x00\x4D\x8D", 
	"xxxx?xx?x????xx??xx")
FUNC_DECL_PATTERN(lua_settable, "53 48 83 EC ? 48 89 ? E8 ? ? ? ? 4C 8B ? ? 4D 8D")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_setfield, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4D\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89\x00\x49\x83\xC8\x00\x0F\x1F\x00\x00\x49\xFF\x00\x43\x80\x3C\x02\x00\x75\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8B\x00\x00\x4C\x8D\x00\x00\x00\x49\x83\xE9", 
	"xx???xxxx?xx?xx?x????xx?xxx?xx??xx?xxxx?x?xx?xx?x????xx??xx???xxx")
FUNC_DECL_PATTERN(lua_setfield, "48 89 ? ? ? 57 48 83 EC ? 4D 89 ? 48 89 ? E8 ? ? ? ? 48 89 ? 49 83 C8 ? 0F 1F ? ? 49 FF ? 43 80 3C 02 ? 75 ? 4C 89 ? 48 89 ? E8 ? ? ? ? 4C 8B ? ? 4C 8D ? ? ? 49 83 E9")

FUNC_DECL_SIG(lua_rawset, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8B\x00\x00\x48\x8B\x00\x4C\x8D", 
	"xx???xx???xxxx?xx?x????xx??xx?xx")
FUNC_DECL_PATTERN(lua_rawset, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 89 ? E8 ? ? ? ? 48 8B ? ? 48 8B ? 4C 8D")

//MINIMAL_HOOK 
FUNC_DECL_SIG(lua_rawseti, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x45\x89\x00\x48\x89\x00\xE8", 
	"xx???xx???xxxx?xx?xx?x")
FUNC_DECL_PATTERN(lua_rawseti, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 45 89 ? 48 89 ? E8")

FUNC_DECL_SIG(lua_setmetatable, 
	"\x53\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x8B\x00\x00\x83\xBA\xF8\xFF\xFF\xFF", 
	"xxxx?xx?x????xx??xxxxxx")
FUNC_DECL_PATTERN(lua_setmetatable, "53 48 83 EC ? 48 89 ? E8 ? ? ? ? 48 8B ? ? 83 BA F8 FF FF FF")

FUNC_DECL_SIG(lua_setfenv, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\xBF\x00\x00\x00\x00\xE8", 
	"xx???xxxx?xx?x????x")
FUNC_DECL_PATTERN(lua_setfenv, "48 89 ? ? ? 57 48 83 EC ? 48 89 ? BF ? ? ? ? E8")

FUNC_DECL_SIG(lua_call, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x8D\x42\x00\x48\x8B", 
	"xx???xxxx?xx?xx")
FUNC_DECL_PATTERN(lua_call, "48 89 ? ? ? 57 48 83 EC ? 8D 42 ? 48 8B")

FUNC_DECL_SIG(lua_pcall, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x44\x89\x00\x41\x89\x00\x48\x89", 
	"xx???xxxx?xx?xx?xx")
FUNC_DECL_PATTERN(lua_pcall, "48 89 ? ? ? 57 48 83 EC ? 44 89 ? 41 89 ? 48 89")

FUNC_DECL_SIG(lua_cpcall, 
	"\x4C\x89\x00\x48\x89\x00\x4D\x89\x00\x48\x89\x00\xE9\x00\x00\x00\x00\x48\x8B", 
	"xx?xx?xx?xx?x????xx")
FUNC_DECL_PATTERN(lua_cpcall, "4C 89 ? 48 89 ? 4D 89 ? 48 89 ? E9 ? ? ? ? 48 8B")

FUNC_DECL_SIG(lua_load, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4D\x85", 
	"xx???xxxx?xx")
FUNC_DECL_PATTERN(lua_load, "48 89 ? ? ? 57 48 83 EC ? 4D 85")

FUNC_DECL_SIG(lua_dump, 
	"\x53\x48\x83\xEC\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x31\x00\x48\x89\x00\x00\x00\x8B\x84", 
	"xxxx?xx?????xx?xx???xx")
FUNC_DECL_PATTERN(lua_dump, "53 48 83 EC ? 48 8B ? ? ? ? ? 48 31 ? 48 89 ? ? ? 8B 84")

//FUNC_DECL_SIG(lua_yield, USING_CODE)

FUNC_DECL_SIG(lua_resume, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x0F\xB6\x00\x00\x48\x89\x00\x3C", 
	"xx???xxxx?xx??xx?x")
FUNC_DECL_PATTERN(lua_resume, "48 89 ? ? ? 57 48 83 EC ? 0F B6 ? ? 48 89 ? 3C")

//FUNC_DECL_SIG(lua_status, USING_CODE)//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)

FUNC_DECL_SIG(lua_gc, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x8B\x00\x00\x33\xFF\x48\x8B\x00\x83\xFA", 
	"xx???xx???xxxx?xx??xxxx?xx")
FUNC_DECL_PATTERN(lua_gc, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 8B ? ? 33 FF 48 8B ? 83 FA")

FUNC_DECL_SIG(lua_error, 
	"\x48\x83\xEC\x00\xE8\x00\x00\x00\x00\x31\xC0\x48\x83\xC4\x00\xC3\xCC\x4C\x8B\x00\x00\x41", 
	"xxx?x????xxxxx?xxxx??x")
FUNC_DECL_PATTERN(lua_error, "48 83 EC ? E8 ? ? ? ? 31 C0 48 83 C4 ? C3 CC 4C 8B ? ? 41")

FUNC_DECL_SIG(lua_next, 
	"\x53\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8B\x00\x00\x48\x8B\x00\x49\x83\xE8", 
	"xxxx?xx?x????xx??xx?xxx")
FUNC_DECL_PATTERN(lua_next, "53 48 83 EC ? 48 89 ? E8 ? ? ? ? 4C 8B ? ? 48 8B ? 49 83 E8")

FUNC_DECL_SIG(lua_concat, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x89\xD3\x48\x89\x00\x83\xFA\x00\x7C", 
	"xx???xxxx?xxxx?xx?x")
FUNC_DECL_PATTERN(lua_concat, "48 89 ? ? ? 57 48 83 EC ? 89 D3 48 89 ? 83 FA ? 7C")

//FUNC_DECL_SIG(lua_getallocf, NO_USE)//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation

//FUNC_DECL_SIG(lua_setallocf, NO_USE)//tex don't really want to mess with allocator function anyway

//FUNC_DECL_SIG(lua_setlevel, NO_USE)//tex: labeled by lua as a hack to be removed in lua 5.2

FUNC_DECL_SIG(lua_getstack, 
	"\x4C\x8B\x00\x00\x49\x89\x00\x85\xD2", 
	"xx??xx?xx")
FUNC_DECL_PATTERN(lua_getstack, "4C 8B ? ? 49 89 ? 85 D2")

FUNC_DECL_SIG(lua_getinfo, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\x31\xFF\x31\xC9", 
	"xx???xx???xx???xxxx?xx?xxxx")
FUNC_DECL_PATTERN(lua_getinfo, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 89 ? 31 FF 31 C9")

FUNC_DECL_SIG(lua_getlocal, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x63\x00\x00\x44\x89", 
	"xx???xx???xx???xxxx?xx??xx")
FUNC_DECL_PATTERN(lua_getlocal, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 63 ? ? 44 89")

FUNC_DECL_SIG(lua_setlocal, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x63\x00\x00\x44\x89\x00\x48\x89\x00\x48\x8D\x00\x00\x48\x8B\x00\x00\x48\x8D\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x49\x89", 
	"xx???xx???xxxx?xx??xx?xx?xx??xx??xx??xx?x????xx")
FUNC_DECL_PATTERN(lua_setlocal, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 63 ? ? 44 89 ? 48 89 ? 48 8D ? ? 48 8B ? ? 48 8D ? ? 48 89 ? E8 ? ? ? ? 49 89")

FUNC_DECL_SIG(lua_getupvalue, 
	"\x48\x83\xEC\x00\x4D\x63\x00\x49\x89", 
	"xxx?xx?xx")
FUNC_DECL_PATTERN(lua_getupvalue, "48 83 EC ? 4D 63 ? 49 89")

FUNC_DECL_SIG(lua_setupvalue, 
	"\x48\x83\xEC\x00\x4D\x63\x00\x4C\x8B\x00\xE8", 
	"xxx?xx?xx?x")
FUNC_DECL_PATTERN(lua_setupvalue, "48 83 EC ? 4D 63 ? 4C 8B ? E8")

FUNC_DECL_SIG(lua_sethook, 
	"\x44\x89\x00\x48\x85\x00\x74\x00\x85\xC0", 
	"xx?xx?x?xx")
FUNC_DECL_PATTERN(lua_sethook, "44 89 ? 48 85 ? 74 ? 85 C0")

//FUNC_DECL_SIG(lua_gethook, USING_CODE)//0x145bd7100)

//FUNC_DECL_SIG(lua_gethookmask, USING_CODE)// 0x14c20f450)

//FUNC_DECL_SIG(lua_gethookcount, USING_CODE)// 0x141a20e40)

//MINIMAL_HOOK
FUNC_DECL_SIG(luaI_openlib, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x41\x00\x41\x00\x41\x00\x48\x83\xEC\x00\x41\x83\xCC", 
	"xx???xx???xx???xx???x?x?x?xxx?xxx")
FUNC_DECL_PATTERN(luaI_openlib, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 41 ? 41 ? 41 ? 48 83 EC ? 41 83 CC")

//FUNC_DECL_SIG(luaL_register, USING_CODE)

FUNC_DECL_SIG(luaL_getmetafield, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x85\xC0\x74", 
	"xx???xxxx?xx?xx?x????xxx")
FUNC_DECL_PATTERN(luaL_getmetafield, "48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 48 89 ? E8 ? ? ? ? 85 C0 74")

FUNC_DECL_SIG(luaL_callmeta, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x8D\x82\x00\x00\x00\x00\x4C\x89", 
	"xx???xx???xxxx?xx????xx")
FUNC_DECL_PATTERN(luaL_callmeta, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 8D 82 ? ? ? ? 4C 89")

FUNC_DECL_SIG(luaL_typerror, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x8B\xFA\x41\x8B\x00\x48\x8B", 
	"xx???xx???xxxx?xxxx?xx")
FUNC_DECL_PATTERN(luaL_typerror, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 8B FA 41 8B ? 48 8B")

FUNC_DECL_SIG(luaL_argerror, 
	"\x53\x56\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x31\x00\x48\x89\x00\x00\x00\x00\x00\x00\x4C\x89\x00\x89\xD3", 
	"xxxxxx????xx?????xx?xx??????xx?xx")
FUNC_DECL_PATTERN(luaL_argerror, "53 56 57 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 31 ? 48 89 ? ? ? ? ? ? 4C 89 ? 89 D3")

FUNC_DECL_SIG(luaL_checklstring, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x89\xD5\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89\x00\x48\x85", 
	"xx???xx???xxxx?xxxx?x????xx?xx")
FUNC_DECL_PATTERN(luaL_checklstring, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 89 D5 48 89 ? E8 ? ? ? ? 48 89 ? 48 85")

FUNC_DECL_SIG(luaL_optlstring, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x4C\x89\x00\x89\xD6\x48\x89\x00\xE8", 
	"xx???xx???xx???xxxx?xx?xx?xxxx?x")
FUNC_DECL_PATTERN(luaL_optlstring, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 4C 89 ? 89 D6 48 89 ? E8")

FUNC_DECL_SIG(luaL_checknumber, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x0F\x29\x00\x00\x00\x89\xD3\x48\x89\x00\xE8\x00\x00\x00\x00\x0F\x57", 
	"xx???xxxx?xx???xxxx?x????xx")
FUNC_DECL_PATTERN(luaL_checknumber, "48 89 ? ? ? 57 48 83 EC ? 0F 29 ? ? ? 89 D3 48 89 ? E8 ? ? ? ? 0F 57")

//FUNC_DECL_SIG(luaL_optnumber, USING_CODE)

FUNC_DECL_SIG(luaL_checkinteger, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x89\xD7\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89\x00\x48\x85\x00\x75", 
	"xx???xx???xxxx?xxxx?x????xx?xx?x")
FUNC_DECL_PATTERN(luaL_checkinteger, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 89 D7 48 89 ? E8 ? ? ? ? 48 89 ? 48 85 ? 75")

FUNC_DECL_SIG(luaL_optinteger, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x89\xD3\x48\x89\x00\xE8\x00\x00\x00\x00\x85\xC0", 
	"xx???xx???xxxx?xx?xxxx?x????xx")
FUNC_DECL_PATTERN(luaL_optinteger, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 89 D3 48 89 ? E8 ? ? ? ? 85 C0")

FUNC_DECL_SIG(luaL_checkstack, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x85\xC0\x75", 
	"xx???xxxx?xx?xx?x????xxx")
FUNC_DECL_PATTERN(luaL_checkstack, "48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 48 89 ? E8 ? ? ? ? 85 C0 75")

FUNC_DECL_SIG(luaL_checktype, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x44\x89\x00\x89\xD7\x48\x89\x00\xE8\x00\x00\x00\x00\x39\xD8", 
	"xx???xx???xxxx?xx?xxxx?x????xx")
FUNC_DECL_PATTERN(luaL_checktype, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 44 89 ? 89 D7 48 89 ? E8 ? ? ? ? 39 D8")

FUNC_DECL_SIG(luaL_checkany, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x89\xD3\x48\x89\x00\xE8\x00\x00\x00\x00\x83\xF8", 
	"xx???xxxx?xxxx?x????xx")
FUNC_DECL_PATTERN(luaL_checkany, "48 89 ? ? ? 57 48 83 EC ? 89 D3 48 89 ? E8 ? ? ? ? 83 F8")

FUNC_DECL_SIG(luaL_newmetatable, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x00\x49\x89\x00\xBA", 
	"xx???xxxx?xx?xx?x")
FUNC_DECL_PATTERN(luaL_newmetatable, "48 89 ? ? ? 57 48 83 EC ? 48 89 ? 49 89 ? BA")

FUNC_DECL_SIG(luaL_checkudata, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x89\xD7\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89", 
	"xx???xx???xx???xxxx?xx?xxxx?x????xx")
FUNC_DECL_PATTERN(luaL_checkudata, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 89 D7 48 89 ? E8 ? ? ? ? 48 89")

FUNC_DECL_SIG(luaL_where, 
	"\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x31\x00\x48\x89\x00\x00\x00\x00\x00\x00\x4C\x8D", 
	"xxxx????xx?????xx?xx??????xx")
FUNC_DECL_PATTERN(luaL_where, "53 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 31 ? 48 89 ? ? ? ? ? ? 4C 8D")

FUNC_DECL_SIG(luaL_error, 
	"\x48\x89\x00\x00\x00\x4C\x89\x00\x00\x00\x4C\x89\x00\x00\x00\x53\x57\x48\x83\xEC", 
	"xx???xx???xx???xxxxx")
FUNC_DECL_PATTERN(luaL_error, "48 89 ? ? ? 4C 89 ? ? ? 4C 89 ? ? ? 53 57 48 83 EC")

FUNC_DECL_SIG(luaL_checkoption, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x00\x4C\x89\x00\x89\xD5", 
	"xx???xx???xx???xxxx?xx?xx?xx")
FUNC_DECL_PATTERN(luaL_checkoption, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 4C 89 ? 4C 89 ? 89 D5")

//FUNC_DECL_SIG(luaL_ref, USING_CODE)//tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info

//FUNC_DECL_SIG(luaL_unref, USING_CODE)

FUNC_DECL_SIG(luaL_loadfile, 
	"\x40\x00\x56\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x33\x00\x48\x89\x00\x00\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x8B", 
	"x?xxxx????xx?????xx?xx??????xx?????xx")
FUNC_DECL_PATTERN(luaL_loadfile, "40 ? 56 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B")

FUNC_DECL_SIG(luaL_loadbuffer, 
	"\x48\x83\xEC\x00\x48\x89\x00\x00\x00\x4C\x89\x00\x00\x00\x4C\x8D\x00\x00\x00\x48\x8D", 
	"xxx?xx???xx???xx???xx")
FUNC_DECL_PATTERN(luaL_loadbuffer, "48 83 EC ? 48 89 ? ? ? 4C 89 ? ? ? 4C 8D ? ? ? 48 8D")

//FUNC_DECL_SIG(luaL_loadstring, USING_CODE)

FUNC_DECL_SIG(luaL_newstate, 
	"\x53\x48\x83\xEC\x00\x48\x8D\x00\x00\x00\x00\x00\x31\xD2\xE8", 
	"xxxx?xx?????xxx")
FUNC_DECL_PATTERN(luaL_newstate, "53 48 83 EC ? 48 8D ? ? ? ? ? 31 D2 E8")

FUNC_DECL_SIG(luaL_gsub, 
	"\x4C\x8B\x00\x55\x49\x8D\x00\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x33\x00\x48\x89\x00\x00\x00\x00\x00\x4D\x89", 
	"xx?xxx?????xxx????xx?????xx?xx?????xx")
FUNC_DECL_PATTERN(luaL_gsub, "4C 8B ? 55 49 8D ? ? ? ? ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? 4D 89")

FUNC_DECL_SIG(luaL_findtable, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x41\x00\x41\x00\x48\x83\xEC\x00\x45\x89", 
	"xx???xx???xx???xx?x?xxx?xx")
FUNC_DECL_PATTERN(luaL_findtable, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 41 ? 41 ? 48 83 EC ? 45 89")

//FUNC_DECL_SIG(luaL_buffinit, USING_CODE)//0x14c1fe910)

FUNC_DECL_SIG(luaL_prepbuffer, 
	"\x57\x48\x83\xEC\x00\x4C\x8B\x00\x48\x89\x00\x49\x29\x00\x49\x83\xE8\x00\x74\x00\x48\x89\x00\x00\x00\x48\x8D\x00\x00\x48\x8B\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\xFF\x47\x00\x48\x89\x00\x48\x89", 
	"xxxx?xx?xx?xx?xxx?x?xx???xx??xx??xx?x????xx?xx?xx")
FUNC_DECL_PATTERN(luaL_prepbuffer, "57 48 83 EC ? 4C 8B ? 48 89 ? 49 29 ? 49 83 E8 ? 74 ? 48 89 ? ? ? 48 8D ? ? 48 8B ? ? 48 89 ? E8 ? ? ? ? FF 47 ? 48 89 ? 48 89")

FUNC_DECL_SIG(luaL_addlstring, 
	"\x4D\x85\x00\x0F\x84\x00\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x41", 
	"xx?xx????xx???xx???x")
FUNC_DECL_PATTERN(luaL_addlstring, "4D 85 ? 0F 84 ? ? ? ? 48 89 ? ? ? 48 89 ? ? ? 41")

//FUNC_DECL_SIG(luaL_addstring, USING_CODE)

FUNC_DECL_SIG(luaL_addvalue, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x8B\x00\x00\x48\x89\x00\x4C\x8D\x00\x00\x00\x48\x89", 
	"xx???xxxx?xx??xx?xx???xx")
FUNC_DECL_PATTERN(luaL_addvalue, "48 89 ? ? ? 57 48 83 EC ? 48 8B ? ? 48 89 ? 4C 8D ? ? ? 48 89")

FUNC_DECL_SIG(luaL_pushresult, 
	"\x57\x48\x83\xEC\x00\x4C\x8B\x00\x48\x89\x00\x49\x29\x00\x49\x83\xE8\x00\x74\x00\x48\x89\x00\x00\x00\x48\x8D\x00\x00\x48\x8B\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\xFF\x47\x00\x48\x89\x00\x48\x8B", 
	"xxxx?xx?xx?xx?xxx?x?xx???xx??xx??xx?x????xx?xx?xx")
FUNC_DECL_PATTERN(luaL_pushresult, "57 48 83 EC ? 4C 8B ? 48 89 ? 49 29 ? 49 83 E8 ? 74 ? 48 89 ? ? ? 48 8D ? ? 48 8B ? ? 48 89 ? E8 ? ? ? ? FF 47 ? 48 89 ? 48 8B")

FUNC_DECL_SIG(luaopen_base, 
	"\x53\x48\x83\xEC\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\xB8", 
	"xxxx?xx?x????xx?????xx?????xx?x????x")
FUNC_DECL_PATTERN(luaopen_base, "53 48 83 EC ? 48 89 ? E8 ? ? ? ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? 48 89 ? E8 ? ? ? ? B8")

FUNC_DECL_SIG(luaopen_table, 
	"\x48\x83\xEC\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x48\x83\xC4\x00\xC3\xCC\x4C\x8B\x00\x00\x48\x83\xEC", 
	"xxx?xx?????xx?????x????x????xxx?xxxx??xxx")
FUNC_DECL_PATTERN(luaopen_table, "48 83 EC ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? B8 ? ? ? ? 48 83 C4 ? C3 CC 4C 8B ? ? 48 83 EC")

FUNC_DECL_SIG(luaopen_io, 
	"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x83\xCA", 
	"xx???xx???xxxx?xx?????xx?x????xx")
FUNC_DECL_PATTERN(luaopen_io, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 8D ? ? ? ? ? 48 89 ? E8 ? ? ? ? 83 CA")

FUNC_DECL_SIG(luaopen_os, 
	"\x48\x83\xEC\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x48\x83\xC4\x00\xC3\xCC\x4C\x8B\x00\x00\x48\x83\xC4", 
	"xxx?xx?????xx?????x????x????xxx?xxxx??xxx")
FUNC_DECL_PATTERN(luaopen_os, "48 83 EC ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? B8 ? ? ? ? 48 83 C4 ? C3 CC 4C 8B ? ? 48 83 C4")

FUNC_DECL_SIG(luaopen_string, 
	"\x53\x48\x83\xEC\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x4C\x8D\x00\x00\x00\x00\x00\x83\xCA", 
	"xxxx?xx?????xx?????xx?x????xx?????xx")
FUNC_DECL_PATTERN(luaopen_string, "53 48 83 EC ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? 48 89 ? E8 ? ? ? ? 4C 8D ? ? ? ? ? 83 CA")

FUNC_DECL_SIG(luaopen_math, 
	"\x53\x48\x83\xEC\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\xE8\x00\x00\x00\x00\x48\x89", 
	"xxxx?xx?????xx?????xx?x????xx")
FUNC_DECL_PATTERN(luaopen_math, "53 48 83 EC ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? 48 89 ? E8 ? ? ? ? 48 89")

FUNC_DECL_SIG(luaopen_debug, 
	"\x48\x83\xEC\x00\x4C\x8D\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x48\x83\xC4\x00\xC3\xCC\x5F", 
	"xxx?xx?????xx?????x????x????xxx?xxx")
FUNC_DECL_PATTERN(luaopen_debug, "48 83 EC ? 4C 8D ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? B8 ? ? ? ? 48 83 C4 ? C3 CC 5F")

FUNC_DECL_SIG(luaopen_package, 
	"\x53\x48\x83\xEC\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\x00\x00\x48\x89\x00\xE8", 
	"xxxx?xx?????xx???xx?x")
FUNC_DECL_PATTERN(luaopen_package, "53 48 83 EC ? 48 8D ? ? ? ? ? 48 89 ? ? ? 48 89 ? E8")

FUNC_DECL_SIG(luaL_openlibs, 
	"\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x8B\x00\x00\x00\x00\x00\x48\x89\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x85", 
	"xx???xxxx?xx?????xx?xx?????xx")
FUNC_DECL_PATTERN(luaL_openlibs, "48 89 ? ? ? 57 48 83 EC ? 48 8B ? ? ? ? ? 48 89 ? 48 8D ? ? ? ? ? 48 85")
