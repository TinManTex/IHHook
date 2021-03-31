#pragma once

//tex macros to declare the various accoutrement required for MH_Hook and straight hooks

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

//tex following macros used in create hooks functions at runtime, requires setup with HOOK* macros

//tex dont need detour, just want original function
#define CREATE_FUNCPTR(name)\
void* name##AddrRebased = (void*)(((size_t)name##Addr - BaseAddr) + RealBaseAddr); \
name = (name##Func*)name##AddrRebased;
//Example use:
//CREATE_FUNCPTR(lua_newstate);
//Expands to:
//void* lua_newstateAddrRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//lua_newstate = (lua_newstateFunc)lua_newstateAddrRebased;


//tex detour and trampoline via MinHook
// Function addresses are from IDA/Ghidra, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
#define CREATE_HOOK(name)\
void* name##Rebased = (void*)(((size_t)name##Addr - BaseAddr) + RealBaseAddr);\
MH_CreateHook(name##Rebased, name##Hook, reinterpret_cast<LPVOID*>(&name));
//Example use:
//CREATE_HOOK(lua_newstate);
//Expands to:
//void* lua_newstateAddrRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//MH_CreateHook(lua_newstateRebased, lua_newstateHook, (LPVOID*)&lua_newstate);

//tex ASSUMES CREATEDETOUR has defined name##Rebased
#define ENABLEHOOK(name) MH_EnableHook(name##Rebased);

#define DEFINEPATTERN(name,signature,mask) char* name##Sig = signature;\
char* name##Mask = mask;


