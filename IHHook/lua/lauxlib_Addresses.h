#pragma once
#include <lauxlib.h>
#include "../HookMacros.h"


//lauxlib.h

//...

HOOKPTR(luaI_openlib, 0x141a0b990);
//OFF HOOKPTR(luaL_register, 0x);//tex: Using default implementation.
HOOKPTR(luaL_getmetafield, 0x14cddb720);
HOOKPTR(luaL_callmeta, 0x14cdd9070);
HOOKPTR(luaL_typerror, 0x141a0bb50);
HOOKPTR(luaL_argerror, 0x14cdd8c20);
HOOKPTR(luaL_checklstring, 0x14cdda000);
HOOKPTR(luaL_optlstring, 0x14cddcd70);
HOOKPTR(luaL_checknumber, 0x14cdda1b0);
//OFF HOOKPTR(luaL_optnumber, 0x//tex: Using default implementation

HOOKPTR(luaL_checkinteger, 0x14cdd9b50);
HOOKPTR(luaL_optinteger, 0x14cddcc80);

HOOKPTR(luaL_checkstack, 0x14cdda5a0);
HOOKPTR(luaL_checktype, 0x14cdda7b0);
HOOKPTR(luaL_checkany, 0x14cdd9a50);

HOOKPTR(luaL_newmetatable, 0x14cddc1f0);
HOOKPTR(luaL_checkudata, 0x14cdda900);

HOOKPTR(luaL_where, 0x14cdde570);
HOOKPTR(luaL_error, 0x14cddaeb0);

HOOKPTR(luaL_checkoption, 0x14cdda430);

//OFF HOOKPTR(luaL_ref, 0x140bec170);//tex: Using default implementation. Unsure on this address, see lauxlib_Creathooks CREATEHOOK(luaL_ref) for more info
//OFF HOOKPTR(luaL_unref, 0x);//tex: Using default implementation.

HOOKPTR(luaL_loadfile, 0x141a0b220);
HOOKPTR(luaL_loadbuffer, 0x14cddbab0);
//OFF HOOKPTR(luaL_loadstring, 0x);//tex: Using default implementation.

HOOKPTR(luaL_newstate, 0x14cddc4f0);


HOOKPTR(luaL_gsub, 0x141a0ada0);

HOOKPTR(luaL_findtable, 0x14cddb150);


//...

/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

HOOKPTR(luaL_buffinit, 0x14cdd8f30);
HOOKPTR(luaL_prepbuffer, 0x14cddd450);
HOOKPTR(luaL_addlstring, 0x141a0a500);
//OFF HOOKPTR(luaL_addstring, 0x//tex: Using default implementation.
HOOKPTR(luaL_addvalue, 0x14cdd8670);
HOOKPTR(luaL_pushresult, 0x14cddd8a0);
