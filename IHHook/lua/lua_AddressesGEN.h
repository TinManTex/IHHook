#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "../HookMacros.h"
//GENERATED: by AddressCSVToMacroHeader.lua
//using D:\GitHub\IHHook\mgstpp-adresses-1.0.15.3.csv

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason - TODO addt to getllocf,setallocf, actually give reason why not (dont want to mess with allocator function)
// USING_CODE - using the default lapi code implementation instead of hooking

HOOKPTR(lua_newstate, 0x141a16790);
HOOKPTR(lua_close, 0x141a16700);
HOOKPTR(lua_newthread, 0x141a117c0);
HOOKPTR(lua_atpanic, 0x146c7d8e6);
//HOOKPTR(lua_gettop, USING_CODE);
HOOKPTR(lua_settop, 0x141a121e0);
HOOKPTR(lua_pushvalue, 0x141a11c40);
HOOKPTR(lua_remove, 0x141a11e90);
HOOKPTR(lua_insert, 0x141a11600);
HOOKPTR(lua_replace, 0x141a11ee0);
HOOKPTR(lua_checkstack, 0x141a10f80);
HOOKPTR(lua_xmove, 0x141a125c0);
HOOKPTR(lua_isnumber, 0x141a11680);
HOOKPTR(lua_isstring, 0x141a116b0);
HOOKPTR(lua_iscfunction, 0x141a11650);
//HOOKPTR(lua_isuserdata, USING_CODE);
HOOKPTR(lua_type, 0x141a12570);
HOOKPTR(lua_typename, 0x141a125a0);
//HOOKPTR(lua_equal, NOT_FOUND);//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
HOOKPTR(lua_rawequal, 0x141a11cc0);
HOOKPTR(lua_lessthan, 0x141a11720);
HOOKPTR(lua_tonumber, 0x141a12460);
HOOKPTR(lua_tointeger, 0x141a12390);//MINIMAL_HOOK 
HOOKPTR(lua_toboolean, 0x141a12330);
HOOKPTR(lua_tolstring, 0x141a123c0);//MINIMAL_HOOK 
HOOKPTR(lua_objlen, 0x141a118b0);
HOOKPTR(lua_tocfunction, 0x141a12360);
HOOKPTR(lua_touserdata, 0x141a12530);
HOOKPTR(lua_tothread, 0x141a12510);
HOOKPTR(lua_topointer, 0x141a124a0);
HOOKPTR(lua_pushnil, 0x141a11ba0);//MINIMAL_HOOK 
HOOKPTR(lua_pushnumber, 0x141a11bc0);
HOOKPTR(lua_pushinteger, 0x141a11af0);//MINIMAL_HOOK 
HOOKPTR(lua_pushlstring, 0x141a11b30);
HOOKPTR(lua_pushstring, 0x141a11be0);//MINIMAL_HOOK 
HOOKPTR(lua_pushvfstring, 0x141a11c70);
HOOKPTR(lua_pushfstring, 0x141a11aa0);
HOOKPTR(lua_pushcclosure, 0x141a119e0);
HOOKPTR(lua_pushboolean, 0x141a119c0);//MINIMAL_HOOK 
HOOKPTR(lua_pushlightuserdata, 0x141a11b10);
HOOKPTR(lua_pushthread, 0x141a11c10);
HOOKPTR(lua_gettable, 0x141a11520);
HOOKPTR(lua_getfield, 0x141a11450);//MINIMAL_HOOK 
HOOKPTR(lua_rawget, 0x141a11d10);
HOOKPTR(lua_rawgeti, 0x141a11d50);//via MACRO lua_getref
HOOKPTR(lua_createtable, 0x141a110f0);//MINIMAL_HOOK 
HOOKPTR(lua_newuserdata, 0x141a11800);
HOOKPTR(lua_getmetatable, 0x141a114c0);
HOOKPTR(lua_getfenv, 0x141a113d0);
HOOKPTR(lua_settable, 0x141a121b0);
HOOKPTR(lua_setfield, 0x141a12070);//MINIMAL_HOOK 
HOOKPTR(lua_rawset, 0x141a11d90);
HOOKPTR(lua_rawseti, 0x141a11e10);//MINIMAL_HOOK 
HOOKPTR(lua_setmetatable, 0x141a120f0);
HOOKPTR(lua_setfenv, 0x141a11fd0);
HOOKPTR(lua_call, 0x141a10f30);
HOOKPTR(lua_pcall, 0x141a11930);
HOOKPTR(lua_cpcall, 0x140bf3030);
HOOKPTR(lua_load, 0x141a11770);
HOOKPTR(lua_dump, 0x141a25070);
//HOOKPTR(lua_yield, USING_CODE);
HOOKPTR(lua_resume, 0x141a13590);
//HOOKPTR(lua_status, USING_CODE);//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
HOOKPTR(lua_gc, 0x141a11220);
HOOKPTR(lua_error, 0x141a11210);
HOOKPTR(lua_next, 0x141a11870);
HOOKPTR(lua_concat, 0x141a11020);
//HOOKPTR(lua_getallocf, NO_USE);//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
//HOOKPTR(lua_setallocf, NO_USE);//tex don't really want to mess with allocator function anyway
//HOOKPTR(lua_setlevel, NO_USE);//tex: labeled by lua as a hack to be removed in lua 5.2
HOOKPTR(lua_getstack, 0x141a20fc0);
HOOKPTR(lua_getinfo, 0x141a20e60);
HOOKPTR(lua_getlocal, 0x141a20f50);
HOOKPTR(lua_setlocal, 0x141a21070);
HOOKPTR(lua_getupvalue, 0x141a11560);
HOOKPTR(lua_setupvalue, 0x141a12240);
HOOKPTR(lua_sethook, 0x141a21040);
HOOKPTR(lua_gethook, 0x14085f1b0);
HOOKPTR(lua_gethookmask, 0x141a20e50);
HOOKPTR(lua_gethookcount, 0x141a20e40);
HOOKPTR(luaI_openlib, 0x141a18300);//MINIMAL_HOOK 
//HOOKPTR(luaL_register, USING_CODE);
HOOKPTR(luaL_getmetafield, 0x141a17690);
HOOKPTR(luaL_callmeta, 0x141a17100);
HOOKPTR(luaL_typerror, 0x141a184c0);
HOOKPTR(luaL_argerror, 0x141a16ff0);
HOOKPTR(luaL_checklstring, 0x141a17210);
HOOKPTR(luaL_optlstring, 0x141a180a0);
HOOKPTR(luaL_checknumber, 0x141a172a0);
//HOOKPTR(luaL_optnumber, USING_CODE);
HOOKPTR(luaL_checkinteger, 0x141a171c0);
HOOKPTR(luaL_optinteger, 0x141a18030);
HOOKPTR(luaL_checkstack, 0x141a173c0);
HOOKPTR(luaL_checktype, 0x141a17400);
HOOKPTR(luaL_checkany, 0x141a17180);
HOOKPTR(luaL_newmetatable, 0x141a17df0);
HOOKPTR(luaL_checkudata, 0x141a17440);
HOOKPTR(luaL_where, 0x141a183f0);
HOOKPTR(luaL_error, 0x141a17500);
HOOKPTR(luaL_checkoption, 0x141a17300);
//HOOKPTR(luaL_ref, USING_CODE);//tex: Unsure on this address, see lauxlib_Creathooks CREATEHOOK(luaL_ref) for more info
//HOOKPTR(luaL_unref, USING_CODE);
HOOKPTR(luaL_loadfile, 0x141a17b90);
HOOKPTR(luaL_loadbuffer, 0x141a17b60);
//HOOKPTR(luaL_loadstring, USING_CODE);
HOOKPTR(luaL_newstate, 0x140bf2c90);
HOOKPTR(luaL_gsub, 0x141a17710);
HOOKPTR(luaL_findtable, 0x141a17560);
HOOKPTR(luaL_buffinit, 0x141a170e0);
HOOKPTR(luaL_prepbuffer, 0x141a18190);
HOOKPTR(luaL_addlstring, 0x141a16e70);
//HOOKPTR(luaL_addstring, USING_CODE);
HOOKPTR(luaL_addvalue, 0x141a16f30);
HOOKPTR(luaL_pushresult, 0x141a181f0);
HOOKPTR(luaopen_base, 0x141a2f4d0);
HOOKPTR(luaopen_table, 0x141a30100);
HOOKPTR(luaopen_io, 0x14c21da00);
HOOKPTR(luaopen_os, 0x141a32190);
HOOKPTR(luaopen_string, 0x141a33610);
HOOKPTR(luaopen_math, 0x141a34dc0);
HOOKPTR(luaopen_debug, 0x141a35cf0);
HOOKPTR(luaopen_package, 0x141a367d0);
HOOKPTR(luaL_openlibs, 0x141a16c00);