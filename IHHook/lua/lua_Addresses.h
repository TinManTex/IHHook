#pragma once
#include <lua.h>
#include "../HookMacros.h"

//lua.h

//...

/*
** state manipulation
*/
HOOKPTR(lua_newstate, 0x14bd561b0);
HOOKPTR(lua_close, 0x141a21660);
HOOKPTR(lua_newthread, 0x14bcdc650);

HOOKPTR(lua_atpanic, 0x14bcd85a0);

/*
** basic stack manipulation
*/
//HOOKPTR(lua_gettop, 0x14cdbb870);//tex: Using default implementation.
HOOKPTR(lua_settop, 0x14bce4c10);
HOOKPTR(lua_pushvalue, 0x14bce09f0);
HOOKPTR(lua_remove, 0x14bce2780);
HOOKPTR(lua_insert, 0x14bcdb790);
HOOKPTR(lua_replace, 0x14bce2e10);
HOOKPTR(lua_checkstack, 0x14bcd88e0);

HOOKPTR(lua_xmove, 0x14bce71d0);

//*
/** access functions (stack -> C)
/*/

HOOKPTR(lua_isnumber, 0x14bcdbaf0);
HOOKPTR(lua_isstring, 0x14bcdbbd0);
HOOKPTR(lua_iscfunction, 0x141a11630);
//HOOKPTR(lua_isuserdata, );//tex: Using default implementation.
HOOKPTR(lua_type, 0x14bce6d00);
HOOKPTR(lua_typename, 0x14bce6ef0);

//HOOKPTR(lua_equal,  );
HOOKPTR(lua_rawequal, 0x14bce1170);
HOOKPTR(lua_lessthan, 0x14bcdc250);

HOOKPTR(lua_tonumber, 0x14bce5ac0);
HOOKPTR(lua_tointeger, 0x14bce55d0);
HOOKPTR(lua_toboolean, 0x14bce4ef0);
HOOKPTR(lua_tolstring, 0x14bce5830);
HOOKPTR(lua_objlen, 0x14bcdcf00);
HOOKPTR(lua_tocfunction, 0x14bce5110);
HOOKPTR(lua_touserdata, 0x14bce6890);
HOOKPTR(lua_tothread, 0x14bce65a0);
HOOKPTR(lua_topointer, 0x14bce61b0);


/*
** push functions (C -> stack)
*/
HOOKPTR(lua_pushnil, 0x14bcded30);
HOOKPTR(lua_pushnumber, 0x14bcdf650);
HOOKPTR(lua_pushinteger, 0x14bcde010);
HOOKPTR(lua_pushlstring, 0x14bcdea10);
HOOKPTR(lua_pushstring, 0x14bcdf720);
HOOKPTR(lua_pushvfstring, 0x14bce0dd0);
HOOKPTR(lua_pushfstring, 0x14bcddd20);
HOOKPTR(lua_pushcclosure, 0x14bcdd990);
HOOKPTR(lua_pushboolean, 0x14bcdd750);
HOOKPTR(lua_pushlightuserdata, 0x14bcde740);
HOOKPTR(lua_pushthread, 0x14bce04a0);

/*
** get functions (Lua -> stack)
*/
HOOKPTR(lua_gettable, 0x14bcdadd0);
HOOKPTR(lua_getfield, 0x14bcda4e0);
HOOKPTR(lua_rawget, 0x14bce1580);
HOOKPTR(lua_rawgeti, 0x14bce17e0);
HOOKPTR(lua_createtable, 0x14bcd9080);
HOOKPTR(lua_newuserdata, 0x14bcdc9c0);
HOOKPTR(lua_getmetatable, 0x141a2e0f0);
HOOKPTR(lua_getfenv, 0x14bcda230);


/*
** set functions (stack -> Lua)
*/
HOOKPTR(lua_settable, 0x14bce48a0);
HOOKPTR(lua_setfield, 0x14bce37a0);
HOOKPTR(lua_rawset, 0x14bce1d00);
HOOKPTR(lua_rawseti, 0x14bce2020);
HOOKPTR(lua_setmetatable, 0x14bce3e70);
HOOKPTR(lua_setfenv, 0x14bce3650);


/*
** `load' and `call' functions (load and run Lua code)
*/
HOOKPTR(lua_call, 0x14bcd8800);
HOOKPTR(lua_pcall, 0x14bcdd4e0);
HOOKPTR(lua_cpcall, 0x148be7750);
HOOKPTR(lua_load, 0x14bcdc480);

HOOKPTR(lua_dump, 0x14bd72b00);

/*
** coroutine functions
*/
//HOOKPTR(lua_yield, );//tex: Using default implementation.
HOOKPTR(lua_resume, 0x14bd46920);
//HOOKPTR(lua_status, 0x141a05a70);//tex: Using default implementation. //tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)

//...

HOOKPTR(lua_gc, 0x141a11200);


/*
** miscellaneous functions
*/

HOOKPTR(lua_error, 0x141a2e070);

HOOKPTR(lua_next, 0x14bcdccc0);

HOOKPTR(lua_concat, 0x14bcd8a70);

//HOOKPTR(lua_getallocf, );
HOOKPTR(lua_setallocf, 0x14bce32d0);

//...

/* hack */
HOOKPTR(lua_setlevel, 0x14bce3a10);

//...

HOOKPTR(lua_getstack, 0x14bd6bff0);
HOOKPTR(lua_getinfo, 0x14bd6b9b0);
HOOKPTR(lua_getlocal, 0x14bd6bd70);
HOOKPTR(lua_setlocal, 0x14bd6c570);
HOOKPTR(lua_getupvalue, 0x14bcdb540);
HOOKPTR(lua_setupvalue, 0x141a12220);
//
HOOKPTR(lua_sethook, 0x14bd6c1f0);
HOOKPTR(lua_gethook, 0x1477e7000);
HOOKPTR(lua_gethookmask, 0x14bd6b4d0);
HOOKPTR(lua_gethookcount, 0x141a20e20);
