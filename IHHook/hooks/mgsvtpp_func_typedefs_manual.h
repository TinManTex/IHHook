#pragma once
//Not generated, manually managed version of the generated version
//for wrangling with stuff you skipped via exportFunc:False
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)
//good practice could be in ghidra to give complex data types good namespaces, 
//then using the export C header option in the datatype manager and including that?
//(though you'll likely have to cull duplicate already included data types)

#include "mgsvtpp_typedefs_ghidra.h" //for ghidra builtin data type names > c++

#include "lua/lua.h"//l_StubbedOutFunc TODO: dont like this

typedef int (__fastcall l_StubbedOutFunc)(lua_State * L);
typedef void (__fastcall nullsub_2Func)(const char * unkSomeIdStr, longlong unkSomeIdNum);

//ZIP: Ghidra repo defines
#define PathCode64(str) PathCode64Ext(str)
typedef ulonglong PathCode64;
typedef uint64_t StrCode;
typedef uint StrCode32;
struct Path {
	PathCode64 Hash;
};
namespace fox {
	struct String {
		char* cString;
		uint64_t length;
		uint64_t hash;
		void* unknown;
	};
};

//CULL, handled in generated version
//tex the (extern of the) function pointers
//extern l_StubbedOutFunc* l_StubbedOut;//EXPORT_FUNC_FALSE
//extern nullsub_2Func* nullsub_2;//EXPORT_FUNC_FALSE
