#pragma once

//tex macros to declare the various accoutrement required for MH_Hook and straight hooks

// Function addresses are from IDA/Ghidra, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
// so it's rebased when its set up (see CREATE_REBASED_ADDR for the simple rebasing math)

//for all hooks need:
//FUNCPTRDEF
//FUNC_DECL_ADDR

//then in runtime:
//just want to use original function
//CREATE_FUNCPTR

//or want to modify the function
//CREATE_REBASED_ADDR, or define name#Addr to the runtime address of the function gained from some other method
//CREATE_HOOK -- DEBUGNOW was CREATEDETOUR
//ENABLE_HOOK

//NOTE: You can just CREATE_FUNCPTR as a matter of course
//and CREATE_HOOK/ENABLE_HOOK after if you want a detour instead


//typedef for the function pointer, 
//and an extern function pointer of the type
//so you can include a header with the hookfunc in other files and use the function
#define FUNCPTRDEF(ret, name, ...)\
typedef ret ( __fastcall name##Func ) (__VA_ARGS__);\
extern name##Func* name;\
extern intptr_t* name##BaseAddr;\
extern intptr_t* name##Addr;
//Example use:
//FUNCPTRDEF(lua_newstate, 0x14cdd7ab0, LuaState*, lua_Alloc f, void *ud);
//Expands to:
//typedef lua_State* (__fastcall *lua_newstateFunc)(lua_Alloc f, void *ud);
//extern lua_newstateFunc lua_newstate;
//extern lua_newstateFunc lua_newstateBaseAddr;
//extern lua_newstateFunc lua_newstateAddr;

//base address of func, and actually declare the function pointer -- can be in header or code (as long as later code using it can see its declaration)
#define FUNC_DECL_ADDR(name, address)\
name##Func* name;\
intptr_t* name##BaseAddr = (intptr_t*)address;\
intptr_t* name##Addr;
//Example use:
//FUNC_DECL_ADDR(lua_newstate, 0x14cdd7ab0);
//Expands to:
//lua_newstateFunc lua_newstate;
//lua_newstateFunc lua_newstateBaseAddr = (lua_newstateFunc)0x14cdd7ab0;
//lua_newstateFunc lua_newstateBaseAddr;

//just want to use original function
//sets the pointer to the rebased address so the function pointer is usable
#define CREATE_FUNCPTR(name)\
intptr_t* name##FuncAddr = (intptr_t*)((name##BaseAddr - BaseAddr) + RealBaseAddr);\
name = (name##Func*)name##FuncAddr;
//Example use:
//CREATE_FUNCPTR(lua_newstate);
//Expands to:
//void* lua_newstateFuncAddr = (void*)((lua_newstateBaseAddr - BaseAddr) + RealBaseAddr);
//lua_newstate = (lua_newstateFunc)lua_newstateFuncAddr;

//Rebases an address an puts it in var for CREATE_HOOK macro
#define CREATE_REBASED_ADDR(name)\
name##Addr = (intptr_t*)((name##BaseAddr - BaseAddr) + RealBaseAddr);
//Example use:
//CREATE_HOOK(lua_newstate);
//Expands to:
//void* lua_newstateAddr = (void*)((lua_newstateBaseAddr - BaseAddr) + RealBaseAddr);


//detour and trampoline via MH_CreateHook
//original function is at the <name> function ptr (just like createptr)
//while the hook/detour is at <name>Hook function pointer.
//ASSUMPTION must have a name##Addr of the runtime location of the function, either via CREATE_REBASED_ADDR or some other means (like a sig scan or other method)
#define CREATE_HOOK(name)\
MH_STATUS name##CreateStatus = MH_CreateHook((LPVOID*)name##Addr, name##Hook, (LPVOID*)&name);\
if (name##CreateStatus != MH_OK) {\
	spdlog::error("MH_CreateHook failed for {} with code {}", "name", name##CreateStatus);\
}
//Example use:
//CREATE_HOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateCreateStatus = MH_CreateHook(lua_newstateAddr, lua_newstateHook, (LPVOID*)&lua_newstate);
//if (lua_newstateCreateStatus != MH_OK) {
//	spdlog::error("MH_CreateHook failed for {} with code {}", "name", lua_newstateCreateStatus);\
//}

//ASSUMPTION name##Addr of runtime memory address has been defined
#define ENABLEHOOK(name)\
MH_STATUS name##EnableStatus = MH_EnableHook((LPVOID*)name##Addr);\
if (name##EnableStatus != MH_OK) {\
	spdlog::error("MH_EnableHook failed for {} with code {}", "name", name##EnableStatus);\
}
//Example use:
//ENABLEHOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateEnableStatus = MH_EnableHook(lua_newstateAddr);
//if (lua_newstateEnableStatus != MH_OK) {
//	spdlog::error("MH_EnableHook failed for {} with code {}", "name", lua_newstateEnableStatus);\
//}

//ASSUMES CREATEDETOUR has defined name##Addr
#define DISABLEHOOK(name)\
MH_STATUS name##DisableStatus = MH_DisableHook((LPVOID*)name##Addr);\
if (name##DisableStatus != MH_OK) {\
	spdlog::error("MH_DisableHook failed for {} with code {}", "name", name##DisableStatus);\
}
//Example use:
//ENABLEHOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateDisableStatus = MH_DisableHook(lua_newstateAddr);
//if (DisableStatus != MH_OK) {
//	spdlog::error("MH_DisableHook failed for {} with code {}", "name", lua_newstateDisableStatus);\
//}

