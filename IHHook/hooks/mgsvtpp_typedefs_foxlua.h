//mgsvtpp_typedefs_foxlua.h
//edited from 'export C header' on foxlua namespace
#pragma once

struct FoxLuaModule {
    struct lua_State* thisAndlua_State;
    struct lua_State* field1_0x8;
    struct lua_State* luastruct_unk1;
    int field3_0x18;
    uint field4_0x1c;
    char* moduleName;
    char field6_0x28;
};