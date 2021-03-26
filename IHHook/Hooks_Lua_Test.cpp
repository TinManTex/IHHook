#include <lua.h>
#include "spdlog/spdlog.h"

namespace IHHook {
void CreateTestTable(lua_State * L) {
	spdlog::debug("lua_createtable");
	lua_createtable(L, 0, 0);
	{
		//tex not really doing much, setting a key to nil is the same as a key that wasnt set lol
		//so the assert should be ok for a simeple test
		spdlog::debug("lua_pushnil");
		lua_pushnil(L);
		assert(lua_type(L, -1) == LUA_TNIL);
		spdlog::debug("lua_setfield");
		lua_setfield(L, -2, "nilfield");

		spdlog::debug("lua_pushboolean");
		lua_pushboolean(L, 1);
		lua_setfield(L, -2, "booleanfield");

		spdlog::debug("lua_pushnumber");
		lua_pushnumber(L, 2.1f);
		lua_setfield(L, -2, "numberfield");

		spdlog::debug("lua_pushinteger");
		lua_pushinteger(L, 3);
		lua_setfield(L, -2, "integerfield");

		spdlog::debug("lua_pushlstring");
		lua_pushlstring(L, "lstringvalue", 12);
		lua_setfield(L, -2, "lstringfield");

		spdlog::debug("lua_pushstring");
		lua_pushstring(L, "stringvalue");
		lua_setfield(L, -2, "stringfield");

		spdlog::debug("lua_settable");
		lua_pushstring(L, "settablekey");
		lua_pushstring(L, "settablevalue");
		lua_settable(L, -3);

		spdlog::debug("lua_rawset");
		lua_pushstring(L, "rawsetkey");
		lua_pushstring(L, "rawsetvalue");
		lua_rawset(L, -3);

		spdlog::debug("lua_rawseti");
		lua_pushstring(L, "rawsetivalue");
		lua_rawseti(L, -2, 1);
	}
	lua_setfield(L, LUA_GLOBALSINDEX, "_IHHook_TestTable");
}//CreateTestTable

void TestHooks_Lua(lua_State* L) {
	spdlog::debug(__func__);
	/*
	** state manipulation
	*/
	//lua_newstate //tested via lua_newstateHook
	//lua_close //TEST not too much point testing this
	spdlog::debug("lua_newthread");
	lua_State* nL = lua_newthread(L);
	assert(nL != NULL);
	int threadStatus = lua_status(nL);
	spdlog::debug("thread status:{}", threadStatus);
	lua_pop(L, 1);//tex newthread adds thread to stack

	//lua_xmove//TEST

	//lua_atpanic //TEST

	/*
	** basic stack manipulation
	*/
	spdlog::debug("lua_gettop");
	int stacksize = lua_gettop(L);
	assert(stacksize == 0);
	spdlog::debug("{}", stacksize);
	
	spdlog::debug("lua_pushinteger");
	lua_pushinteger(L, 1);
	stacksize = lua_gettop(L);
	assert(stacksize == 1);
	spdlog::debug("{}", stacksize);

	spdlog::debug("lua_pushinteger");
	lua_pushinteger(L, 2);
	stacksize = lua_gettop(L);
	assert(stacksize == 2);
	spdlog::debug("{}", stacksize);

	spdlog::debug("lua_pushinteger");
	lua_pushinteger(L, 3);
	stacksize = lua_gettop(L);
	assert(stacksize == 3);
	spdlog::debug("{}", stacksize);

	//stack has 3 integers (1,2,3)

	//shrink stack to 2 elements
	spdlog::debug("lua_settop");
	lua_settop(L, 2);
	stacksize = lua_gettop(L);
	assert(stacksize == 2);
	spdlog::debug("{}", stacksize);

	//push a copy of element 1 (an int == 1) to top of stack
	spdlog::debug("lua_pushvalue");
	lua_pushvalue(L, 1);
	spdlog::debug("lua_tointeger");
	int integer = (int)lua_tointeger(L, -1);
	assert(integer == 1);
	spdlog::debug("{}", integer);

	//stack should be ints (1,2,1)

	//remove top of stack (int==1)
	spdlog::debug("lua_remove");
	lua_remove(L, 1);
	integer = (int)lua_tointeger(L, 1);
	assert(integer == 2);
	spdlog::debug("{}", integer);

	//stack should be ints (2,1)

	//push 2 to top, 
	spdlog::debug("lua_insert");
	lua_insert(L, 1);
	integer = (int)lua_tointeger(L, 1);
	assert(integer == 1);
	spdlog::debug("{}", integer);
	
	//stack should be ints (1,2)

	spdlog::debug("lua_replace");
	lua_replace(L, 1);
	integer = (int)lua_tointeger(L, 1);
	assert(integer == 2);
	spdlog::debug("{}", integer);

	//stack should be int (2)

	spdlog::debug("lua_pushinteger");
	lua_pushinteger(L, 2);
	
	// stack should be ints (2,2)

	//lua_equal//TEST

	spdlog::debug("lua_rawequal");
	int equal =	lua_rawequal(L, 1, 2);
	assert(equal == 1);
	spdlog::debug("{}", equal);

	spdlog::debug("lua_pushinteger");
	lua_pushinteger(L, 1);

	// stack should be ints (2,2,1)

	spdlog::debug("lua_lessthan");
	int lesthan = lua_lessthan(L, 3, 2);
	assert(lesthan == 1);
	spdlog::debug("{}", lesthan);

	//tex cant think of a good test for this right now (but really these tests are more about seeing if the hooked function actually calls/doesn't crash rather than testing the actual lua api correctness)
	spdlog::debug("lua_checkstack");
	int cangrow = lua_checkstack(L, 5);
	assert(cangrow == 1);

	//tex clear stack for rest of tests
	spdlog::debug("lua_settop");
	lua_settop(L, 0);
	stacksize = lua_gettop(L);
	assert(stacksize == 0);
	spdlog::debug("{}", stacksize);


	CreateTestTable(L);

	spdlog::debug("lua_getfield _IHHook_TestTable");
	lua_getfield(L, LUA_GLOBALSINDEX, "_IHHook_TestTable");
	{
		//lua_toboolean
		spdlog::debug("lua_gettable");
		lua_pushstring(L, "booleanfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_toboolean");
		int booleanfield = lua_toboolean(L, -1);
		lua_pop(L, 1);
		assert(booleanfield == 1);
		spdlog::debug("{}", booleanfield);

		//lua_tonumber
		lua_pushstring(L, "numberfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_tonumber");
		double numberfield = lua_tonumber(L, -1);
		lua_pop(L, 1);
		assert(numberfield == 2.1f);
		spdlog::debug("{}", numberfield);

		//lua_tointeger
		lua_pushstring(L, "integerfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_tointeger");
		int integerfield = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);
		assert(integerfield == 3);
		spdlog::debug("{}", integerfield);

		//lua_tostring
		lua_pushstring(L, "stringfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_tostring");
		const char * stringfield = lua_tostring(L, -1);
		lua_pop(L, 1);
		spdlog::debug("'{}'", stringfield);
	}
	lua_pop(L, 1);//_IHHook_TestTable, doubles as lua_settop test (well it would if we hadn't already used pop before this point)

	{
		spdlog::debug("lua_gettop");
		stacksize = lua_gettop(L);
		assert(stacksize == 0);
		spdlog::debug("{}", stacksize);
	}

	spdlog::debug("lua_getfield _IHHook_TestTable");
	lua_getfield(L, LUA_GLOBALSINDEX, "_IHHook_TestTable");
	{
		lua_pushstring(L, "stringfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_type stringfield");
		int stringtype = lua_type(L, -1);
		lua_pop(L, 1);
		assert(stringtype == LUA_TSTRING);
		spdlog::debug("{}", stringtype);

		const char* stringtypename = lua_typename(L, stringtype);
		assert(std::string(stringtypename) == "string");
		spdlog::debug(stringtypename);

		lua_pushstring(L, "stringfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_isstring stringfield");
		int isstring = lua_isstring(L, -1);
		lua_pop(L, 1);
		assert(isstring == 1);
		spdlog::debug("{}", isstring);

		lua_pushstring(L, "numberfield");
		lua_gettable(L, -2);
		spdlog::debug("lua_isnumber numberfield");
		int isnumber = lua_isnumber(L, -1);
		lua_pop(L, 1);
		assert(isnumber == 1);
		spdlog::debug("{}", isnumber);

		lua_pushstring(L, "settablekey");
		lua_gettable(L, -2);
		const char * settablefield = lua_tostring(L, -1);
		lua_pop(L, 1);
		assert(std::string(settablefield) == "settablevalue");
		spdlog::debug("settablekey:'{}'", settablefield);

		spdlog::debug("lua_rawget");
		lua_pushstring(L, "rawsetkey");
		lua_rawget(L, -2);
		const char * rawsetkeyfield = lua_tostring(L, -1);
		lua_pop(L, 1);
		assert(std::string(rawsetkeyfield) == "rawsetvalue");
		spdlog::debug("rawsetkey:'{}'", rawsetkeyfield);

		spdlog::debug("lua_rawgeti");
		lua_rawgeti(L, -1, 1);
		const char * rawsetifield = lua_tostring(L, -1);
		lua_pop(L, 1);
		assert(std::string(rawsetifield) == "rawsetivalue");
		spdlog::debug("rawseti 1:'{}'", rawsetifield);


	}
	lua_pop(L, 1);

	//
	spdlog::debug("lua_getfield _IHHook_TestTable");
	lua_getfield(L, LUA_GLOBALSINDEX, "_IHHook_TestTable");
	spdlog::debug("while lua_next");
	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		spdlog::debug("{} - {}",
			lua_typename(L, lua_type(L, -2)),
			lua_typename(L, lua_type(L, -1)));
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}
}//TestHooks_Lua

//tex testing after libs registered
void TestHooks_Lua_PostLibs(lua_State * L) {
	spdlog::debug(__func__);
	lua_getfield(L, LUA_GLOBALSINDEX, "IHH");
	{
		lua_pushstring(L, "OnUpdate");
		lua_gettable(L, -2);
		spdlog::debug("lua_iscfunction OnUpdate");
		int iscfunction = lua_iscfunction(L, -1);
		lua_pop(L, 1);
		assert(iscfunction == 1);
		spdlog::debug("{}", iscfunction);
	}
	lua_pop(L, 1);
}//TestHooks_Lua_PostLibs
}//namespace ihhook