/*
** $Id: lualib.h,v 1.36.1.1 2007/12/27 13:02:25 roberto Exp $
** Lua standard libraries
** See Copyright Notice in lua.h
*/
//tex: Butchered fwd decls to func pointers. Search //OFF , FUNCPTRDEF
#include "../HookMacros.h" //tex
#include "hooks/mgsvtpp_func_typedefs.h"

#ifndef lualib_h
#define lualib_h

#include "lua.h"


/* Key to file-handle type */
#define LUA_FILEHANDLE		"FILE*"


#define LUA_COLIBNAME	"coroutine"
FUNCPTRDEF(int, luaopen_base, lua_State *L);

#define LUA_TABLIBNAME	"table"
FUNCPTRDEF(int, luaopen_table, lua_State *L);

#define LUA_IOLIBNAME	"io"
FUNCPTRDEF(int, luaopen_io, lua_State *L);

#define LUA_OSLIBNAME	"os"
FUNCPTRDEF(int, luaopen_os, lua_State *L);

#define LUA_STRLIBNAME	"string"
FUNCPTRDEF(int, luaopen_string, lua_State *L);

#define LUA_MATHLIBNAME	"math"
FUNCPTRDEF(int, luaopen_math, lua_State *L);

#define LUA_DBLIBNAME	"debug"
FUNCPTRDEF(int, luaopen_debug, lua_State *L);

#define LUA_LOADLIBNAME	"package"
FUNCPTRDEF(int, luaopen_package, lua_State *L);


/* open all previous libraries */
FUNCPTRDEF(void, luaL_openlibs, lua_State *L);



#ifndef lua_assert
#define lua_assert(x)	((void)0)
#endif


#endif
