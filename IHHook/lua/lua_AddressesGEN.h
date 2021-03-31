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

FUNC_DECL_ADDR(lua_newstate, 0x14c1fc960);
FUNC_DECL_ADDR(lua_close, 0x14c1fc380);
FUNC_DECL_ADDR(lua_newthread, 0x14c1d9d90);
FUNC_DECL_ADDR(lua_atpanic, 0x14c1d5120);
//FUNC_DECL_ADDR(lua_gettop, USING_CODE);
FUNC_DECL_ADDR(lua_settop, 0x14c1ebbe0);
FUNC_DECL_ADDR(lua_pushvalue, 0x14c1e87e0);
FUNC_DECL_ADDR(lua_remove, 0x14c1ea0c0);
FUNC_DECL_ADDR(lua_insert, 0x14c1d8150);
FUNC_DECL_ADDR(lua_replace, 0x14c1ea370);
FUNC_DECL_ADDR(lua_checkstack, 0x14c1d5900);
FUNC_DECL_ADDR(lua_xmove, 0x14c1edcd0);
FUNC_DECL_ADDR(lua_isnumber, 0x14c1d8c90);
FUNC_DECL_ADDR(lua_isstring, 0x14c1d9250);
FUNC_DECL_ADDR(lua_iscfunction, 0x141a11650);
//FUNC_DECL_ADDR(lua_isuserdata, USING_CODE);
FUNC_DECL_ADDR(lua_type, 0x14c1ed760);
FUNC_DECL_ADDR(lua_typename, 0x14c1eda50);
//FUNC_DECL_ADDR(lua_equal, NOT_FOUND);//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
FUNC_DECL_ADDR(lua_rawequal, 0x14c1e8d70);
FUNC_DECL_ADDR(lua_lessthan, 0x14c1d9890);
FUNC_DECL_ADDR(lua_tonumber, 0x14c1ecdd0);
FUNC_DECL_ADDR(lua_tointeger, 0x14c1ec760);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_toboolean, 0x14c1ebe40);
FUNC_DECL_ADDR(lua_tolstring, 0x14c1eca70);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_objlen, 0x14c1da960);
FUNC_DECL_ADDR(lua_tocfunction, 0x14c1ec560);
FUNC_DECL_ADDR(lua_touserdata, 0x14c1ed4b0);
FUNC_DECL_ADDR(lua_tothread, 0x14c1ed3c0);
FUNC_DECL_ADDR(lua_topointer, 0x14c1ed230);
FUNC_DECL_ADDR(lua_pushnil, 0x14c1e7cc0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushnumber, 0x14c1e7dd0);
FUNC_DECL_ADDR(lua_pushinteger, 0x14c1e6ef0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushlstring, 0x14c1e7310);
FUNC_DECL_ADDR(lua_pushstring, 0x14c1e7ee0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushvfstring, 0x14c1e8b10);
FUNC_DECL_ADDR(lua_pushfstring, 0x14c1e6a70);
FUNC_DECL_ADDR(lua_pushcclosure, 0x14c1e67b0);
FUNC_DECL_ADDR(lua_pushboolean, 0x14c1db230);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_pushlightuserdata, 0x14c1e71b0);
FUNC_DECL_ADDR(lua_pushthread, 0x14c1e86a0);
FUNC_DECL_ADDR(lua_gettable, 0x14c1d7c10);
FUNC_DECL_ADDR(lua_getfield, 0x14c1d7320);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_rawget, 0x14c1e9190);
FUNC_DECL_ADDR(lua_rawgeti, 0x14c1e9320);//via MACRO lua_getref
FUNC_DECL_ADDR(lua_createtable, 0x14c1d6320);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_newuserdata, 0x14c1d9f80);
FUNC_DECL_ADDR(lua_getmetatable, 0x14c1d79b0);
FUNC_DECL_ADDR(lua_getfenv, 0x14c1d7160);
FUNC_DECL_ADDR(lua_settable, 0x14c1eb2b0);
FUNC_DECL_ADDR(lua_setfield, 0x14c1eabb0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_rawset, 0x14c1e9cf0);
FUNC_DECL_ADDR(lua_rawseti, 0x14c1e9ff0);//MINIMAL_HOOK 
FUNC_DECL_ADDR(lua_setmetatable, 0x14c1eb040);
FUNC_DECL_ADDR(lua_setfenv, 0x14c1eaa00);
FUNC_DECL_ADDR(lua_call, 0x14c1d5690);
FUNC_DECL_ADDR(lua_pcall, 0x14c1daff0);
FUNC_DECL_ADDR(lua_cpcall, 0x146c7dd00);
FUNC_DECL_ADDR(lua_load, 0x14c1d99c0);
FUNC_DECL_ADDR(lua_dump, 0x14c217460);
//FUNC_DECL_ADDR(lua_yield, USING_CODE);
FUNC_DECL_ADDR(lua_resume, 0x14c1f0d80);
//FUNC_DECL_ADDR(lua_status, USING_CODE);//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
FUNC_DECL_ADDR(lua_gc, 0x141a11220);
FUNC_DECL_ADDR(lua_error, 0x14c1d6c90);
FUNC_DECL_ADDR(lua_next, 0x14c1da770);
FUNC_DECL_ADDR(lua_concat, 0x14c1d5d50);
//FUNC_DECL_ADDR(lua_getallocf, NO_USE);//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
//FUNC_DECL_ADDR(lua_setallocf, NO_USE);//tex don't really want to mess with allocator function anyway
//FUNC_DECL_ADDR(lua_setlevel, NO_USE);//tex: labeled by lua as a hack to be removed in lua 5.2
FUNC_DECL_ADDR(lua_getstack, 0x14c20fbd0);
FUNC_DECL_ADDR(lua_getinfo, 0x14c20f650);
FUNC_DECL_ADDR(lua_getlocal, 0x14c20f880);
FUNC_DECL_ADDR(lua_setlocal, 0x14c20fff0);
FUNC_DECL_ADDR(lua_getupvalue, 0x14c1d7ea0);
FUNC_DECL_ADDR(lua_setupvalue, 0x141a12240);
FUNC_DECL_ADDR(lua_sethook, 0x14c20fde0);
FUNC_DECL_ADDR(lua_gethook, 0x145bd7100);
FUNC_DECL_ADDR(lua_gethookmask, 0x14c20f450);
FUNC_DECL_ADDR(lua_gethookcount, 0x141a20e40);
FUNC_DECL_ADDR(luaI_openlib, 0x141a18300);//MINIMAL_HOOK 
//FUNC_DECL_ADDR(luaL_register, USING_CODE);
FUNC_DECL_ADDR(luaL_getmetafield, 0x14c200d50);
FUNC_DECL_ADDR(luaL_callmeta, 0x14c1fec20);
FUNC_DECL_ADDR(luaL_typerror, 0x141a184c0);
FUNC_DECL_ADDR(luaL_argerror, 0x14c1fe5f0);
FUNC_DECL_ADDR(luaL_checklstring, 0x14c1ff790);
FUNC_DECL_ADDR(luaL_optlstring, 0x14c201de0);
FUNC_DECL_ADDR(luaL_checknumber, 0x14c1ffb30);
//FUNC_DECL_ADDR(luaL_optnumber, USING_CODE);
FUNC_DECL_ADDR(luaL_checkinteger, 0x14c1ff430);
FUNC_DECL_ADDR(luaL_optinteger, 0x14c201a70);
FUNC_DECL_ADDR(luaL_checkstack, 0x14c200010);
FUNC_DECL_ADDR(luaL_checktype, 0x14c2004c0);
FUNC_DECL_ADDR(luaL_checkany, 0x14c1ff2f0);
FUNC_DECL_ADDR(luaL_newmetatable, 0x14c2013c0);
FUNC_DECL_ADDR(luaL_checkudata, 0x14c200630);
FUNC_DECL_ADDR(luaL_where, 0x14c203350);
FUNC_DECL_ADDR(luaL_error, 0x14c2008f0);
FUNC_DECL_ADDR(luaL_checkoption, 0x14c1ffd60);
//FUNC_DECL_ADDR(luaL_ref, USING_CODE);//tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info
//FUNC_DECL_ADDR(luaL_unref, USING_CODE);
FUNC_DECL_ADDR(luaL_loadfile, 0x141a17b90);
FUNC_DECL_ADDR(luaL_loadbuffer, 0x14c200f90);
//FUNC_DECL_ADDR(luaL_loadstring, USING_CODE);
FUNC_DECL_ADDR(luaL_newstate, 0x14c201490);
FUNC_DECL_ADDR(luaL_gsub, 0x141a17710);
FUNC_DECL_ADDR(luaL_findtable, 0x14c200aa0);
FUNC_DECL_ADDR(luaL_buffinit, 0x14c1fe910);
FUNC_DECL_ADDR(luaL_prepbuffer, 0x14c202140);
FUNC_DECL_ADDR(luaL_addlstring, 0x141a16e70);
//FUNC_DECL_ADDR(luaL_addstring, USING_CODE);
FUNC_DECL_ADDR(luaL_addvalue, 0x14c1fd9b0);
FUNC_DECL_ADDR(luaL_pushresult, 0x14c202280);
FUNC_DECL_ADDR(luaopen_base, 0x14c21d5c0);
FUNC_DECL_ADDR(luaopen_table, 0x14c21d8d0);
FUNC_DECL_ADDR(luaopen_io, 0x14c21da00);
FUNC_DECL_ADDR(luaopen_os, 0x14c21e020);
FUNC_DECL_ADDR(luaopen_string, 0x14c21e720);
FUNC_DECL_ADDR(luaopen_math, 0x14c21e800);
FUNC_DECL_ADDR(luaopen_debug, 0x14c21ea00);
FUNC_DECL_ADDR(luaopen_package, 0x14c21ee20);
FUNC_DECL_ADDR(luaL_openlibs, 0x14c1fd0c0);