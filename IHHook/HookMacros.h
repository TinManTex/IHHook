#pragma once

//tex macros to declare the various accoutrement required for MH_Hook and straight hooks

// Function addresses are from IDA/Ghidra, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
// so it's rebased when its set up (see CREATE_ for the simple rebasing math)

//tex: for all hooks need:
//FUNCPTRDEF
//FUNC_DECL_ADDR

//then in runtime:
//just want to use original function
//CREATE_FUNCPTR

//or want to modify the function
//CREATE_HOOK -- DEBUGNOW was CREATEDETOUR
//MH_STATUS status; //not a macro, just a var for enablehook to log the status of it trying to hook, define once in scope for any number of uses of ENABLEHOOK 
//ENABLE_HOOK

//NOTE: You can just CREATE_FUNCPTR as a matter of course
//and CREATE_HOOK/ENABLE_HOOK after if you want a detour instead


//tex typedef for the function pointer, 
//and an extern function pointer of the type
//so you can include a header with the hookfunc in other files and use the function
#define FUNCPTRDEF(ret, name, ...)\
typedef ret ( __fastcall name##Func ) (__VA_ARGS__);\
extern name##Func* name;\
extern name##Func* name##Addr;\
//Example use:
//FUNCPTRDEF(lua_newstate, 0x14cdd7ab0, LuaState*, lua_Alloc f, void *ud);
//Expands to:
//typedef lua_State* (__fastcall *lua_newstateFunc)(lua_Alloc f, void *ud);
//extern lua_newstateFunc lua_newstate;
//extern lua_newstateFunc lua_newstateAddr;

//base address of func, and actually declare the function pointer -- can be in header or code (as long as later code using it can see its declaration)
#define FUNC_DECL_ADDR(name, address)\
name##Func* name;\
name##Func* name##Addr = (name##Func*)address;\
//Example use:
//FUNC_DECL_ADDR(lua_newstate, 0x14cdd7ab0);
//Expands to:
//lua_newstateFunc lua_newstate;
//lua_newstateFunc lua_newstateFuncAddr = (lua_newstateFunc)0x14cdd7ab0;

//just want to use original function
//sets the pointer to the rebased address so the function pointer is usable
#define CREATE_FUNCPTR(name)\
void* name##AddrRebased = (void*)(((size_t)name##Addr - BaseAddr) + RealBaseAddr); \
name = (name##Func*)name##AddrRebased;
//Example use:
//CREATE_FUNCPTR(lua_newstate);
//Expands to:
//void* lua_newstateAddrRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//lua_newstate = (lua_newstateFunc)lua_newstateAddrRebased;


//tex detour and trampoline via MinHook
#define CREATE_HOOK(name)\
void* name##Rebased = (void*)(((size_t)name##Addr - BaseAddr) + RealBaseAddr);\
MH_CreateHook(name##Rebased, name##Hook, reinterpret_cast<LPVOID*>(&name));
//Example use:
//CREATE_HOOK(lua_newstate);
//Expands to:
//void* lua_newstateAddrRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//MH_CreateHook(lua_newstateRebased, lua_newstateHook, (LPVOID*)&lua_newstate);

//tex ASSUMES CREATEDETOUR has defined name##Rebased
#define ENABLEHOOK(name)\
MH_STATUS name##Status = MH_EnableHook(name##Rebased);\
if (name##Status != MH_OK) {\
	spdlog::error("MH_EnableHook failed for {} with code {}", "name", name##Status);\
}

#define DEFINEPATTERN(name,signature,mask) char* name##Sig = signature;\
char* name##Mask = mask;


