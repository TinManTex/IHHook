#pragma once
//Not generated, manually managed version of the generated version
//for wrangling with stuff you skipped via exportFunc:False
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)

#include "lua/lua.h"//l_StubbedOutFunc TODO: dont like this

typedef int (__fastcall l_StubbedOutFunc)(lua_State * L);
typedef void (__fastcall nullsub_2Func)(const char * unkSomeIdStr, longlong unkSomeIdNum);

//ZIP: Fox Defines
namespace fox {
	struct String {
		char* cString;
		uint64_t length;
		uint64_t hash;
		void* unknown;
	};
	struct Path {
		ulonglong Hash;
	};
};
typedef uint64_t StrCode;
typedef uint StrCode32;
typedef uint PathCode64s;
typedef fox::Path* (__fastcall GetEmptyPathFunc)(void);
typedef fox::Path* (__fastcall Path_CopyFunc)(fox::Path* param1, fox::Path* rhs);
typedef StrCode(__fastcall GetStrCodeWithLengthFunc)(const char* buf, longlong len);
typedef StrCode32(__fastcall GetStrCode32Func)(const char* str);
typedef void(__fastcall LoadFileSubFunc)(PathCode64s pathA, PathCode64s pathB); //ZIP: Workaround for Function/Name conflict

//CULL, handled in generated version
//tex the (extern of the) function pointers
//extern l_StubbedOutFunc* l_StubbedOut;//EXPORT_FUNC_FALSE
//extern nullsub_2Func* nullsub_2;//EXPORT_FUNC_FALSE
