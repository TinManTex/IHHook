#pragma once
//Not generated, manually managed version of the generated version
//for wrangling with stuff you skipped via exportFunc:False
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)

#include "lua/lua.h"//l_StubbedOutFunc TODO: dont like this

typedef int (__fastcall l_StubbedOutFunc)(lua_State * L);
typedef void (__fastcall nullsub_2Func)(const char * unkSomeIdStr, longlong unkSomeIdNum);

//ZIP: Ghidra repo defines
typedef uint64_t StrCode;
typedef uint StrCode32;
typedef ulonglong PathCode64s;
struct Path {
	PathCode64s Hash;
};
namespace fox {
	struct String {
		char* cString;
		uint64_t length;
		uint64_t hash;
		void* unknown;
	};
};
typedef void(__fastcall LoadFileSubFunc)(PathCode64s pathA, PathCode64s pathB); //ZIP: Workaround for Function/Enum name conflict
typedef Path* (__fastcall Path_CopyFunc)(Path* This, Path* rhs);

//CULL, handled in generated version
//tex the (extern of the) function pointers
//extern l_StubbedOutFunc* l_StubbedOut;//EXPORT_FUNC_FALSE
//extern nullsub_2Func* nullsub_2;//EXPORT_FUNC_FALSE
