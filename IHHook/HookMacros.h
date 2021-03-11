#pragma once

//tex macros to declare the various accoutrement required for MH_Hook and straight hooks

//tex typedef for the function pointers
#define HOOKFUNC(ret, name, ...) typedef ret ( __fastcall name##Func ) (__VA_ARGS__);\
	extern name##Func* name;
//Example use:
//FUNCINFO_WITHHOOK(lua_newstate, 0x14cdd7ab0, LuaState*, lua_Alloc f, void *ud);
//Expands to:
//typedef lua_State* (__fastcall *lua_newstateFunc)(lua_Alloc f, void *ud);
//lua_newstateFunc lua_newstate;

//tex declare function pointer, using address in respect to module base, this will be rebased and overwritten at runtime using CREATEHOOK. Kinda hinky, but it saves having to set up yet another variable.
#define HOOKPTR(name, address) name##Func* name = (name##Func*)address;
//Example use:
//HOOKPTR(lua_newstate, 0x14cdd7ab0);
//Expands to:
//lua_newstateFunc name = (lua_newstate)address;
//NOTE: CREATEHOOK (defined below) is used to rebase this pointer

//tex following macros used in create hooks functions at runtime, requires setup with HOOK* macros

//tex dont need detour, just want original function
#define CREATEHOOK(name) void* name##Rebased = (void*)(((size_t)name - BaseAddr) + RealBaseAddr); \
name = (name##Func*)name##Rebased;
//Example use:
//CREATEHOOK(lua_newstate);
//Expands to:
//void* lua_newstateRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//lua_newstate = (lua_newstateFunc)lua_newstateRebased;


//tex detour and trampoline via MinHook
// Function addresses are from IDA/Ghidra, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
#define CREATEDETOUR(name) void* name##Rebased = (void*)(((size_t)name - BaseAddr) + RealBaseAddr);\
MH_CreateHook(name##Rebased, name##Hook, reinterpret_cast<LPVOID*>(&name));
//Example use:
//CREATEHOOK(lua_newstate);
//Expands to:
//void* lua_newstateAddrRebased = (void*)((lua_newstateAddr - BaseAddr) + RealBaseAddr);
//MH_CreateHook(lua_newstateAddrRebased, lua_newstateHook, (LPVOID*)&lua_newstate);

//tex ASSUMES CREATEHOOK has already rebased address, still defines name##Rebased since MH_EnableHook wants the original address and MH_CreateHook will be overwriting the pointer since I'm reusing original name.
#define CREATEDETOURB(name) void* name##Rebased = (void*)name;\
MH_CreateHook((void*)name, name##Hook, reinterpret_cast<LPVOID*>(&name));

//tex ASSUMES CREATEDETOUR has defined name##Rebased
#define ENABLEHOOK(name) MH_EnableHook(name##Rebased);

#define DEFINEPATTERN(name,signature,mask) char* name##Sig = signature;\
char* name##Mask = mask;


