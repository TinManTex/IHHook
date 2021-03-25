#pragma once
#include <lauxlib.h>
#include "../HookMacros.h"


//lauxlib.h

//...

HOOKPTR(luaI_openlib, 0x141a18300);//1.0.15.2 = 0x141a182e0);//MINIMAL_HOOK
DEFINEPATTERN(luaI_openlib,
	"\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9",
	"xx?x????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
)
//OFF HOOKPTR(luaL_register, 0x);//tex: Using default implementation.
HOOKPTR(luaL_getmetafield, 0x14bd59c00);
HOOKPTR(luaL_callmeta, 0x14bd576f0);
HOOKPTR(luaL_typerror, 0x141a184a0);
HOOKPTR(luaL_argerror, 0x14bd56f20);
HOOKPTR(luaL_checklstring, 0x14bd58540);
HOOKPTR(luaL_optlstring, 0x14bd5be10);
HOOKPTR(luaL_checknumber, 0x14bd58850);
//OFF HOOKPTR(luaL_optnumber, 0x//tex: Using default implementation

HOOKPTR(luaL_checkinteger, 0x14bd581c0);
HOOKPTR(luaL_optinteger, 0x14bd5b470);

HOOKPTR(luaL_checkstack, 0x14bd590b0);
HOOKPTR(luaL_checktype, 0x14bd591b0);
HOOKPTR(luaL_checkany, 0x14bd57c90);

HOOKPTR(luaL_newmetatable, 0x14bd5a820);
HOOKPTR(luaL_checkudata, 0x14bd59460);

HOOKPTR(luaL_where, 0x14bd5ce00);
HOOKPTR(luaL_error, 0x14bd59760);

HOOKPTR(luaL_checkoption, 0x14bd58ac0);

//OFF HOOKPTR(luaL_ref, );//tex: Using default implementation. Unsure on this address, see lauxlib_Creathooks CREATEHOOK(luaL_ref) for more info
//OFF HOOKPTR(luaL_unref, 0x);//tex: Using default implementation.

HOOKPTR(luaL_loadfile, 0x141a17b70);
HOOKPTR(luaL_loadbuffer, 0x14bd59d80);
//OFF HOOKPTR(luaL_loadstring, 0x);//tex: Using default implementation.

HOOKPTR(luaL_newstate, 0x14bd561b0);


HOOKPTR(luaL_gsub, 0x141a176f0);

HOOKPTR(luaL_findtable, 0x14bd598d0);


//...

/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

HOOKPTR(luaL_buffinit, 0x14bd572a0);
HOOKPTR(luaL_prepbuffer, 0x14bd5c3e0);
HOOKPTR(luaL_addlstring, 0x141a16e50);
//OFF HOOKPTR(luaL_addstring, 0x//tex: Using default implementation.
HOOKPTR(luaL_addvalue, 0x14bd56e20);
HOOKPTR(luaL_pushresult, 0x14bd5c6e0);
