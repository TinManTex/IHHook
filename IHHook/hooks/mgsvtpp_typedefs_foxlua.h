//mgsvtpp_typedefs_foxlua.h
//edited from 'export C header' on foxlua namespace
#pragma once

namespace foxlua {
    struct luastate_unk1 {
        struct lua_State* thisAndlua_State;
        struct lua_State* field1_0x8;
        struct lua_State* field2_0x10;
        undefined4 field3_0x18;
        int field4_0x1c;
        struct lua_State* field5_0x20;
        undefined field6_0x28;
    };

    struct module {
        struct lua_State* thisAndlua_State;
        struct lua_State* field1_0x8;
        struct lua_State* luastruct_unk1;
        int field3_0x18;
        uint field4_0x1c;
        char* moduleName;
        char field6_0x28;
    };
}//namespace foxlua