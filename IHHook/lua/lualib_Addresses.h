#pragma once
#include "../HookMacros.h"
#include <lualib.h>


//lualib.h

//...

HOOKPTR(luaopen_base, 0x14bd7b150);

HOOKPTR(luaopen_table, 0x14bd7b420);

HOOKPTR(luaopen_io, 0x14bd7b720);

HOOKPTR(luaopen_os, 0x14bd7bb40);

HOOKPTR(luaopen_string, 0x14bd7bea0);

HOOKPTR(luaopen_math, 0x14bd7c1e0);

HOOKPTR(luaopen_debug, 0x14bd7c560);

HOOKPTR(luaopen_package, 0x14bd7c780);

HOOKPTR(luaL_openlibs, 0x14c1fd0c0);//1.0.15.2 =  0x14bd56910);//MINIMAL_HOOK
