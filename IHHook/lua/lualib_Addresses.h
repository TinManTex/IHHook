#pragma once
#include "../HookMacros.h"
#include <lualib.h>


//lualib.h

//...

HOOKPTR(luaopen_base, 0x14cdfa900);

HOOKPTR(luaopen_table, 0x14cdfaf30);

HOOKPTR(luaopen_io, 0x14cdfb500);

HOOKPTR(luaopen_os, 0x14cdfbec0);

HOOKPTR(luaopen_string, 0x14cdfc020);

HOOKPTR(luaopen_math, 0x14cdfc220);

HOOKPTR(luaopen_debug, 0x14cdfc4c0);

HOOKPTR(luaopen_package, 0x14cdfc6b0);

HOOKPTR(luaL_openlibs, 0x14cdd7f20);
