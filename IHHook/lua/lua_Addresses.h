#pragma once
#include <lua.h>
#include "../HookMacros.h"

//lua.h

//...

/*
** state manipulation
*/
HOOKPTR(lua_newstate, 0x14cdd7ab0);
HOOKPTR(lua_close, 0x14cdd7850);
HOOKPTR(lua_newthread, 0x14cdbd160);

HOOKPTR(lua_atpanic, 0x14cdb8560);

/*
** basic stack manipulation
*/
HOOKPTR(lua_gettop, 0x14cdbb870);
HOOKPTR(lua_settop, 0x14cdc3810);
HOOKPTR(lua_pushvalue, 0x14cdc05b0);
HOOKPTR(lua_remove, 0x141a22aa0);
HOOKPTR(lua_insert, 0x141a04d40);
HOOKPTR(lua_replace, 0x14cdc2590);
HOOKPTR(lua_checkstack, 0x14cdb88a0);

HOOKPTR(lua_xmove, 0x14cdc55d0);

//*
/** access functions (stack -> C)
/*/

HOOKPTR(lua_isnumber, 0x14cdbc190);
HOOKPTR(lua_isstring, 0x14cdbc490);
HOOKPTR(lua_iscfunction, 0x14cdbbdc0);
//HOOKPTR(lua_isuserdata, );//tex: Using default implementation.
HOOKPTR(lua_type, 0x14cdc5270);
HOOKPTR(lua_typename, 0x14cdc5540);

//HOOKPTR(lua_equal,  );
HOOKPTR(lua_rawequal,  0x14cdc0ec0);
HOOKPTR(lua_lessthan, 0x14cdbca50);

HOOKPTR(lua_tonumber, 0x14cdc46f0);
HOOKPTR(lua_tointeger, 0x14cdc4180);
HOOKPTR(lua_toboolean, 0x14cdc3af0);
HOOKPTR(lua_tolstring, 0x14cdc4430);
HOOKPTR(lua_objlen, 0x14cdbdec0);
HOOKPTR(lua_tocfunction, 0x14cdc3c70);
HOOKPTR(lua_touserdata, 0x14cdc4e30);
HOOKPTR(lua_tothread,  0x14cdc4af0);
HOOKPTR(lua_topointer, 0x14cdc4850);


/*
** push functions (C -> stack)
*/
HOOKPTR(lua_pushnil, 0x14cdbfb40);
HOOKPTR(lua_pushnumber, 0x14cdbfeb0);
HOOKPTR(lua_pushinteger, 0x14cdbec00);
HOOKPTR(lua_pushlstring, 0x14cdbf290);
HOOKPTR(lua_pushstring, 0x14cdc00e0);
HOOKPTR(lua_pushvfstring, 0x14cdc0880);
HOOKPTR(lua_pushfstring, 0x14cdbe870);
HOOKPTR(lua_pushcclosure, 0x14cdbe580);
HOOKPTR(lua_pushboolean, 0x14cdbe360);
HOOKPTR(lua_pushlightuserdata, 0x14cdbedb0);
HOOKPTR(lua_pushthread, 0x14cdc04c0);

/*
** get functions (Lua -> stack)
*/
HOOKPTR(lua_gettable, 0x14cdbb1d0);
HOOKPTR(lua_getfield, 0x14cdba900);
HOOKPTR(lua_rawget, 0x14cdc14c0);
HOOKPTR(lua_rawgeti, 0x14cdc1860);
HOOKPTR(lua_createtable, 0x14cdb90e0);
HOOKPTR(lua_newuserdata, 0x14cdbd440);
HOOKPTR(lua_getmetatable, 0x14cdbafa0);
HOOKPTR(lua_getfenv, 0x14cdba720);


/*
** set functions (stack -> Lua)
*/
HOOKPTR(lua_settable, 0x14cdc3590);
HOOKPTR(lua_setfield, 0x14cdc30d0);
HOOKPTR(lua_rawset, 0x14cdc1bc0);
HOOKPTR(lua_rawseti, 0x14cdc2020);
HOOKPTR(lua_setmetatable, 0x14cdc3370);
HOOKPTR(lua_setfenv, 0x14cdc2b30);


/*
** `load' and `call' functions (load and run Lua code)
*/
HOOKPTR(lua_call, 0x14cdb8670);
HOOKPTR(lua_pcall, 0x14cdbe140);
HOOKPTR(lua_cpcall, 0x147e9d220);
HOOKPTR(lua_load, 0x14cdbd030);

HOOKPTR(lua_dump, 0x141a048a0);

/*
** coroutine functions
*/
//HOOKPTR(lua_yield, );//tex: Using default implementation.
HOOKPTR(lua_resume, 0x14cdc9330);
HOOKPTR(lua_status, 0x141a05a70);

//...

HOOKPTR(lua_gc, 0x141a04960);


/*
** miscellaneous functions
*/

HOOKPTR(lua_error, 0x14cdba560);

HOOKPTR(lua_next, 0x14cdbd570);

HOOKPTR(lua_concat, 0x14cdb8bc0);

//HOOKPTR(lua_getallocf, );
//HOOKPTR(lua_setallocf, );

//...

/* hack */
HOOKPTR(lua_setlevel, 0x14cdc32d0);

//...

HOOKPTR(lua_getstack, 0x14cded2c0);
HOOKPTR(lua_getinfo, 0x141a144f0);
HOOKPTR(lua_getlocal, 0x14cded050);
HOOKPTR(lua_setlocal, 0x14cded700);
//HOOKPTR(lua_getupvalue, );
//HOOKPTR(lua_setupvalue, );
//
HOOKPTR(lua_sethook, 0x14cded4a0);
HOOKPTR(lua_gethook, 0x14cdec220);
HOOKPTR(lua_gethookmask, 0x14cdecd80);
HOOKPTR(lua_gethookcount, 0x140956a10);
