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

FUNC_DECL_ADDR(lua_newstate, 0x14c9a52c0);
FUNC_DECL_ADDR(lua_close, 0x14c9a5100);
FUNC_DECL_ADDR(lua_newthread, 0x14c989a70);
FUNC_DECL_ADDR(lua_atpanic, 0x14c9855b0);
//FUNC_DECL_ADDR(lua_gettop, USING_CODE);
FUNC_DECL_ADDR(lua_settop, 0x14c990ed0);
FUNC_DECL_ADDR(lua_pushvalue, 0x14c98e1d0);
FUNC_DECL_ADDR(lua_remove, 0x14c98f0f0);
FUNC_DECL_ADDR(lua_insert, 0x14c9888d0);
FUNC_DECL_ADDR(lua_replace, 0x14c98f490);
FUNC_DECL_ADDR(lua_checkstack, 0x14c985da0);
FUNC_DECL_ADDR(lua_xmove, 0x14c993c00);
FUNC_DECL_ADDR(lua_isnumber, 0x14c988960);
FUNC_DECL_ADDR(lua_isstring, 0x14c988ca0);
FUNC_DECL_ADDR(lua_iscfunction, 0x141a11770);
//FUNC_DECL_ADDR(lua_isuserdata, USING_CODE);
FUNC_DECL_ADDR(lua_type, 0x14c9935f0);
FUNC_DECL_ADDR(lua_typename, 0x14c993970);
//FUNC_DECL_ADDR(lua_equal, NOT_FOUND);//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
FUNC_DECL_ADDR(lua_rawequal, 0x14c98e690);
FUNC_DECL_ADDR(lua_lessthan, 0x14c989590);
FUNC_DECL_ADDR(lua_tonumber, 0x14c9924d0);
FUNC_DECL_ADDR(lua_tointeger, 0x14c991b80);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_toboolean, 0x14c991120);
FUNC_DECL_ADDR(lua_tolstring, 0x14c992060);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_objlen, 0x14c98a230);
FUNC_DECL_ADDR(lua_tocfunction, 0x14c991460);
FUNC_DECL_ADDR(lua_touserdata, 0x14c992e00);
FUNC_DECL_ADDR(lua_tothread, 0x14c992bc0);
FUNC_DECL_ADDR(lua_topointer, 0x14c992610);
FUNC_DECL_ADDR(lua_pushnil, 0x14c98d570);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushnumber, 0x14c98d800);
FUNC_DECL_ADDR(lua_pushinteger, 0x14c98c7c0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushlstring, 0x14c98ccc0);
FUNC_DECL_ADDR(lua_pushstring, 0x14c98dcb0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushvfstring, 0x14c98e4a0);
FUNC_DECL_ADDR(lua_pushfstring, 0x14c98c4b0);
FUNC_DECL_ADDR(lua_pushcclosure, 0x14c98c080);
FUNC_DECL_ADDR(lua_pushboolean, 0x14c98b310);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushlightuserdata, 0x14c98c9e0);
FUNC_DECL_ADDR(lua_pushthread, 0x14c98df80);
FUNC_DECL_ADDR(lua_gettable, 0x14c987b90);
FUNC_DECL_ADDR(lua_getfield, 0x14c987300);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_rawget, 0x14c98e930);
FUNC_DECL_ADDR(lua_rawgeti, 0x14c98ebc0);//via MACRO lua_getref
FUNC_DECL_ADDR(lua_createtable, 0x14c986520);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_newuserdata, 0x14c989bf0);
FUNC_DECL_ADDR(lua_getmetatable, 0x14c9878c0);
FUNC_DECL_ADDR(lua_getfenv, 0x14c987110);
FUNC_DECL_ADDR(lua_settable, 0x14c990bd0);
FUNC_DECL_ADDR(lua_setfield, 0x14c990870);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_rawset, 0x14c98ed50);
FUNC_DECL_ADDR(lua_rawseti, 0x14c98efe0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_setmetatable, 0x14c990a80);
FUNC_DECL_ADDR(lua_setfenv, 0x14c98f9f0);
FUNC_DECL_ADDR(lua_call, 0x14c9859f0);
FUNC_DECL_ADDR(lua_pcall, 0x14c98acb0);
FUNC_DECL_ADDR(lua_cpcall, 0x1489e59c0);
FUNC_DECL_ADDR(lua_load, 0x14c9898e0);
FUNC_DECL_ADDR(lua_dump, 0x14caa27a0);
//FUNC_DECL_ADDR(lua_yield, USING_CODE);
FUNC_DECL_ADDR(lua_resume, 0x14c996a10);
//FUNC_DECL_ADDR(lua_status, USING_CODE);//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
FUNC_DECL_ADDR(lua_gc, 0x141a11340);
FUNC_DECL_ADDR(lua_error, 0x14c986ea0);
FUNC_DECL_ADDR(lua_next, 0x14c98a010);
FUNC_DECL_ADDR(lua_concat, 0x14c986010);
//FUNC_DECL_ADDR(lua_getallocf, NO_USE);//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
//FUNC_DECL_ADDR(lua_setallocf, NO_USE);//tex don't really want to mess with allocator function anyway
//FUNC_DECL_ADDR(lua_setlevel, NO_USE);//tex: labeled by lua as a hack to be removed in lua 5.2
FUNC_DECL_ADDR(lua_getstack, 0x14ca99b40);
FUNC_DECL_ADDR(lua_getinfo, 0x14ca993e0);
FUNC_DECL_ADDR(lua_getlocal, 0x14ca99980);
FUNC_DECL_ADDR(lua_setlocal, 0x14ca9a230);
FUNC_DECL_ADDR(lua_getupvalue, 0x14c9884b0);
FUNC_DECL_ADDR(lua_setupvalue, 0x141a12360);
FUNC_DECL_ADDR(lua_sethook, 0x14ca99f50);
FUNC_DECL_ADDR(lua_gethook, 0x1484f0140);
FUNC_DECL_ADDR(lua_gethookmask, 0x14aa5c6b0);
FUNC_DECL_ADDR(lua_gethookcount, 0x14095c060);
FUNC_DECL_ADDR(luaI_openlib, 0x141a18410);//MINIMAL_HOOK 
//FUNC_DECL_ADDR(luaL_register, USING_CODE);
FUNC_DECL_ADDR(luaL_getmetafield, 0x14c9a9020);
FUNC_DECL_ADDR(luaL_callmeta, 0x14c9a6740);
FUNC_DECL_ADDR(luaL_typerror, 0x141a185d0);
FUNC_DECL_ADDR(luaL_argerror, 0x14c9a5ff0);
FUNC_DECL_ADDR(luaL_checklstring, 0x14c9a72e0);
FUNC_DECL_ADDR(luaL_optlstring, 0x14c9aac90);
FUNC_DECL_ADDR(luaL_checknumber, 0x14c9a7490);
//FUNC_DECL_ADDR(luaL_optnumber, USING_CODE);
FUNC_DECL_ADDR(luaL_checkinteger, 0x14c9a6db0);
FUNC_DECL_ADDR(luaL_optinteger, 0x14c9aa940);
FUNC_DECL_ADDR(luaL_checkstack, 0x14c9a7ab0);
FUNC_DECL_ADDR(luaL_checktype, 0x14c9a8030);
FUNC_DECL_ADDR(luaL_checkany, 0x14c9a6b30);
FUNC_DECL_ADDR(luaL_newmetatable, 0x14c9a9f50);
FUNC_DECL_ADDR(luaL_checkudata, 0x14c9a8430);
FUNC_DECL_ADDR(luaL_where, 0x14c9ac500);
FUNC_DECL_ADDR(luaL_error, 0x14c9a8870);
FUNC_DECL_ADDR(luaL_checkoption, 0x14c9a7600);
//FUNC_DECL_ADDR(luaL_ref, USING_CODE);//tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info
//FUNC_DECL_ADDR(luaL_unref, USING_CODE);
FUNC_DECL_ADDR(luaL_loadfile, 0x141a17ca0);
FUNC_DECL_ADDR(luaL_loadbuffer, 0x14c9a98c0);
//FUNC_DECL_ADDR(luaL_loadstring, USING_CODE);
//FUNC_DECL_ADDR(luaL_newstate, NOT_FOUND);//DEBUGNOW NOT_FOUND
FUNC_DECL_ADDR(luaL_gsub, 0x141a17820);
FUNC_DECL_ADDR(luaL_findtable, 0x14c9a8a20);
FUNC_DECL_ADDR(luaL_buffinit, 0x14c9a6230);
FUNC_DECL_ADDR(luaL_prepbuffer, 0x14c9ab0c0);
FUNC_DECL_ADDR(luaL_addlstring, 0x141a16f80);
//FUNC_DECL_ADDR(luaL_addstring, USING_CODE);
FUNC_DECL_ADDR(luaL_addvalue, 0x14c9a5d20);
FUNC_DECL_ADDR(luaL_pushresult, 0x14c9ab8b0);
FUNC_DECL_ADDR(luaopen_base, 0x14caa9570);
FUNC_DECL_ADDR(luaopen_table, 0x14caa9640);
FUNC_DECL_ADDR(luaopen_io, 0x14caa9bb0);
FUNC_DECL_ADDR(luaopen_os, 0x141a32280);
FUNC_DECL_ADDR(luaopen_string, 0x14caaa490);
FUNC_DECL_ADDR(luaopen_math, 0x14caaa7d0);
FUNC_DECL_ADDR(luaopen_debug, 0x14caaab70);
FUNC_DECL_ADDR(luaopen_package, 0x141a368c0);
FUNC_DECL_ADDR(luaL_openlibs, 0x14c9a5860);