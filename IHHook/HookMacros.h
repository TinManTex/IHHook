#pragma once

#include "MinHook.h"
#include "MemoryUtils.h"
#include <map>

#include "Hooking.Patterns/Hooking.Patterns.h"//DEBUGNOW

namespace IHHook {
	extern std::map<std::string, int64_t> addressSet;
}

//DEBUGNOW put this somewhere or CULL
	//DEBUGNOW signatures are more robust to game updates/different game versions than straight addresses, but take a long time to search
	//since IHHook is started on it's own thread game initialisation will continue, and IHHook wont be ready in time to start up IH properly.
	//an alternative would be to do a hook to an early execution point of the game and init  ihhook there,
	//but given the low rate of updates of the game it's better to stick with direct addresses, but have signatures documented as a backup


//tex macros to declare the various accoutrement required for MH_Hook and straight hooks

// Function addresses are from IDA/Ghidra, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
// so it's rebased when its set up (see GET_REBASED_ADDR for the simple rebasing math)

//Signatures currently grabbed using GH SigMaker
//https://guidedhacking.com/resources/guided-hacking-x64-cheat-engine-sigmaker-plugin-ce-7-2.319/
//DEBUGNOW only need one type sig&mask or pattern, but have yet to decide on which to use (sigmaker grabs both so there's no real issue on generating
//though I prefer pattern for easier manual comparing without having to jump back and forth between sig and mask, seems all the sigmatching funcs I have currently gathered so far are sig&mask

//DEBUGNOW update this
//also document isTargetExe

//for all hooks need:
//FUNCPTRDEF
//FUNC_DECL_ADDR

//then in runtime:
//just want to use original function
//CREATE_FUNCPTR

//or want to modify the function
//GET_REBASED_ADDR, or define name#Addr to the runtime address of the function gained from some other method
//CREATE_HOOK -- DEBUGNOW was CREATEDETOUR
//ENABLE_HOOK

//NOTE: You can just CREATE_FUNCPTR as a matter of course
//and CREATE_HOOK/ENABLE_HOOK after if you want a detour instead

#define STRINGIFY(x) #x
#define TOKENPASTE(x, y) STRINGIFY(x ## y)


//TODO CULL
#define FUNCPTRDEF(ret, name, ...)\
//


//just want to use original function
//sets the pointer to the rebased address so the function pointer is usable
#define CREATE_FUNCPTR(name)\
name = (name##Func*)addressSet[#name];
//Example use:
//CREATE_FUNCPTR(lua_newstate);
//Expands to:
//lua_newstate = (lua_newstateFunc*)addressSet["lua_newstate"];

//detour and trampoline via MH_CreateHook,
//original function is at the <name> function ptr (just like createptr)
//while the hook/detour is at <name>Hook function pointer.
//ASSUMPTION must have a name##Addr of the runtime location of the function, either via GET_REBASED_ADDR or some other means (like a sig scan or other method)
#define CREATE_HOOK(name)\
MH_STATUS name##CreateStatus = MH_CreateHook((LPVOID*)addressSet[#name], name##Hook, (LPVOID*)&name);\
if (name##CreateStatus != MH_OK) {\
	spdlog::error("MH_CreateHook failed for {} with code {}", #name, name##CreateStatus);\
} else {\
	spdlog::debug("MH_CreateHook MH_OK for {}", #name);\
}
//Example use:
//CREATE_HOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateCreateStatus = MH_CreateHook((LPVOID*)addressSet["lua_newstate"], lua_newstateHook, (LPVOID*)&lua_newstate);
//if (lua_newstateCreateStatus != MH_OK) {
//	spdlog::error("MH_CreateHook failed for {} with code {}", "lua_newstate", lua_newstateCreateStatus);\
//}

//ASSUMPTION name##Addr of runtime memory address has been defined
#define ENABLEHOOK(name)\
MH_STATUS name##EnableStatus = MH_EnableHook((LPVOID*)addressSet[#name]);\
if (name##EnableStatus != MH_OK) {\
	spdlog::error("MH_EnableHook failed for {} with code {}", #name, name##EnableStatus);\
} else {\
	spdlog::debug("MH_EnableHook MH_OK for {}", #name);\
}
//Example use:
//ENABLEHOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateEnableStatus = MH_EnableHook((LPVOID*)addressSet["lua_newstate"]);
//if (lua_newstateEnableStatus != MH_OK) {
//	spdlog::error("MH_EnableHook failed for {} with code {}", "lua_newstate", lua_newstateEnableStatus);\
//}

//ASSUMES CREATEDETOUR has defined name##Addr
#define DISABLEHOOK(name)\
MH_STATUS name##DisableStatus = MH_DisableHook((LPVOID*)addressSet[#name]);\
if (name##DisableStatus != MH_OK) {\
	spdlog::error("MH_DisableHook failed for {} with code {}", #name, name##DisableStatus);\
} else {\
	spdlog::debug("MH_DisableHook MH_OK for {}", #name);\
}
//Example use:
//ENABLEHOOK(lua_newstate);
//Expands to:
//MH_STATUS lua_newstateDisableStatus = MH_DisableHook((LPVOID*)addressSet["lua_newstate"]);
//if (DisableStatus != MH_OK) {
//	spdlog::error("MH_DisableHook failed for {} with code {}", "lua_newstate", lua_newstateDisableStatus);\
//}

