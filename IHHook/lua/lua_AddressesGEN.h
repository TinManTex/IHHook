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

HOOKPTR(lua_newstate, 0x14c1fc960);
HOOKPTR(lua_close, 0x14c1fc380);
HOOKPTR(lua_newthread, 0x14c1d9d90);
HOOKPTR(lua_atpanic, 0x14c1d5120);
//HOOKPTR(lua_gettop, USING_CODE);
HOOKPTR(lua_settop, 0x14c1ebbe0);
HOOKPTR(lua_pushvalue, 0x14c1e87e0);
HOOKPTR(lua_remove, 0x14c1ea0c0);
HOOKPTR(lua_insert, 0x14c1d8150);
HOOKPTR(lua_replace, 0x14c1ea370);
HOOKPTR(lua_checkstack, 0x14c1d5900);
HOOKPTR(lua_xmove, 0x14c1edcd0);
HOOKPTR(lua_isnumber, 0x14c1d8c90);
HOOKPTR(lua_isstring, 0x14c1d9250);
HOOKPTR(lua_iscfunction, 0x141a11650);
//HOOKPTR(lua_isuserdata, USING_CODE);
HOOKPTR(lua_type, 0x14c1ed760);
HOOKPTR(lua_typename, 0x14c1eda50);
//HOOKPTR(lua_equal, NOT_FOUND);//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
HOOKPTR(lua_rawequal, 0x14c1e8d70);
HOOKPTR(lua_lessthan, 0x14c1d9890);
HOOKPTR(lua_tonumber, 0x14c1ecdd0);
HOOKPTR(lua_tointeger, 0x14c1ec760);//MINIMAL_HOOK 
HOOKPTR(lua_toboolean, 0x14c1ebe40);
HOOKPTR(lua_tolstring, 0x14c1eca70);//MINIMAL_HOOK 
HOOKPTR(lua_objlen, 0x14c1da960);
HOOKPTR(lua_tocfunction, 0x14c1ec560);
HOOKPTR(lua_touserdata, 0x14c1ed4b0);
HOOKPTR(lua_tothread, 0x14c1ed3c0);
HOOKPTR(lua_topointer, 0x14c1ed230);
HOOKPTR(lua_pushnil, 0x14c1e7cc0);//MINIMAL_HOOK 
HOOKPTR(lua_pushnumber, 0x14c1e7dd0);
HOOKPTR(lua_pushinteger, 0x14c1e6ef0);//MINIMAL_HOOK 
HOOKPTR(lua_pushlstring, 0x14c1e7310);
HOOKPTR(lua_pushstring, 0x14c1e7ee0);//MINIMAL_HOOK 
HOOKPTR(lua_pushvfstring, 0x14c1e8b10);
HOOKPTR(lua_pushfstring, 0x14c1e6a70);
HOOKPTR(lua_pushcclosure, 0x14c1e67b0);
HOOKPTR(lua_pushboolean, 0x14c1db230);//MINIMAL_HOOK 
HOOKPTR(lua_pushlightuserdata, 0x14c1e71b0);
HOOKPTR(lua_pushthread, 0x14c1e86a0);
HOOKPTR(lua_gettable, 0x14c1d7c10);
HOOKPTR(lua_getfield, 0x14c1d7320);//MINIMAL_HOOK 
HOOKPTR(lua_rawget, 0x14c1e9190);
HOOKPTR(lua_rawgeti, 0x14c1e9320);//via MACRO lua_getref
HOOKPTR(lua_createtable, 0x14c1d6320);//MINIMAL_HOOK 
HOOKPTR(lua_newuserdata, 0x14c1d9f80);
HOOKPTR(lua_getmetatable, 0x14c1d79b0);
HOOKPTR(lua_getfenv, 0x14c1d7160);
HOOKPTR(lua_settable, 0x14c1eb2b0);
HOOKPTR(lua_setfield, 0x14c1eabb0);//MINIMAL_HOOK 
HOOKPTR(lua_rawset, 0x14c1e9cf0);
HOOKPTR(lua_rawseti, 0x14c1e9ff0);//MINIMAL_HOOK 
HOOKPTR(lua_setmetatable, 0x14c1eb040);
HOOKPTR(lua_setfenv, 0x14c1eaa00);
HOOKPTR(lua_call, 0x14c1d5690);
HOOKPTR(lua_pcall, 0x14c1daff0);
HOOKPTR(lua_cpcall, 0x146c7dd00);
HOOKPTR(lua_load, 0x14c1d99c0);
HOOKPTR(lua_dump, 0x14c217460);
//HOOKPTR(lua_yield, USING_CODE);
HOOKPTR(lua_resume, 0x14c1f0d80);
//HOOKPTR(lua_status, USING_CODE);//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
HOOKPTR(lua_gc, 0x141a11220);
HOOKPTR(lua_error, 0x14c1d6c90);
HOOKPTR(lua_next, 0x14c1da770);
HOOKPTR(lua_concat, 0x14c1d5d50);
//HOOKPTR(lua_getallocf, NO_USE);//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
//HOOKPTR(lua_setallocf, NO_USE);//tex don't really want to mess with allocator function anyway
//HOOKPTR(lua_setlevel, NO_USE);//tex: labeled by lua as a hack to be removed in lua 5.2
HOOKPTR(lua_getstack, 0x14c20fbd0);
HOOKPTR(lua_getinfo, 0x14c20f650);
HOOKPTR(lua_getlocal, 0x14c20f880);
HOOKPTR(lua_setlocal, 0x14c20fff0);
HOOKPTR(lua_getupvalue, 0x14c1d7ea0);
HOOKPTR(lua_setupvalue, 0x141a12240);
HOOKPTR(lua_sethook, 0x14c20fde0);
HOOKPTR(lua_gethook, 0x145bd7100);
HOOKPTR(lua_gethookmask, 0x14c20f450);
HOOKPTR(lua_gethookcount, 0x141a20e40);
HOOKPTR(luaI_openlib, 0x141a18300);//MINIMAL_HOOK 
//HOOKPTR(luaL_register, USING_CODE);
HOOKPTR(luaL_getmetafield, 0x14c200d50);
HOOKPTR(luaL_callmeta, 0x14c1fec20);
HOOKPTR(luaL_typerror, 0x141a184c0);
HOOKPTR(luaL_argerror, 0x14c1fe5f0);
HOOKPTR(luaL_checklstring, 0x14c1ff790);
HOOKPTR(luaL_optlstring, 0x14c201de0);
HOOKPTR(luaL_checknumber, 0x14c1ffb30);
//HOOKPTR(luaL_optnumber, USING_CODE);
HOOKPTR(luaL_checkinteger, 0x14c1ff430);
HOOKPTR(luaL_optinteger, 0x14c201a70);
HOOKPTR(luaL_checkstack, 0x14c200010);
HOOKPTR(luaL_checktype, 0x14c2004c0);
HOOKPTR(luaL_checkany, 0x14c1ff2f0);
HOOKPTR(luaL_newmetatable, 0x14c2013c0);
HOOKPTR(luaL_checkudata, 0x14c200630);
HOOKPTR(luaL_where, 0x14c203350);
HOOKPTR(luaL_error, 0x14c2008f0);
HOOKPTR(luaL_checkoption, 0x14c1ffd60);
//HOOKPTR(luaL_ref, USING_CODE);//tex: Unsure on this address, see lauxlib_Creathooks CREATEHOOK(luaL_ref) for more info
//HOOKPTR(luaL_unref, USING_CODE);
HOOKPTR(luaL_loadfile, 0x141a17b90);
HOOKPTR(luaL_loadbuffer, 0x14c200f90);
//HOOKPTR(luaL_loadstring, USING_CODE);
HOOKPTR(luaL_newstate, 0x14c201490);
HOOKPTR(luaL_gsub, 0x141a17710);
HOOKPTR(luaL_findtable, 0x14c200aa0);
HOOKPTR(luaL_buffinit, 0x14c1fe910);
HOOKPTR(luaL_prepbuffer, 0x14c202140);
HOOKPTR(luaL_addlstring, 0x141a16e70);
//HOOKPTR(luaL_addstring, USING_CODE);
HOOKPTR(luaL_addvalue, 0x14c1fd9b0);
HOOKPTR(luaL_pushresult, 0x14c202280);
HOOKPTR(luaopen_base, 0x14c21d5c0);
HOOKPTR(luaopen_table, 0x14c21d8d0);
HOOKPTR(luaopen_io, 0x14c21da00);
HOOKPTR(luaopen_os, 0x14c21e020);
HOOKPTR(luaopen_string, 0x14c21e720);
HOOKPTR(luaopen_math, 0x14c21e800);
HOOKPTR(luaopen_debug, 0x14c21ea00);
HOOKPTR(luaopen_package, 0x14c21ee20);
HOOKPTR(luaL_openlibs, 0x14c1fd0c0);