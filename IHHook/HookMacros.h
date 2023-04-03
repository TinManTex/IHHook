#pragma once

#include "MinHook.h"
#include "MemoryUtils.h"
#include <map>

#include "Hooking.Patterns/Hooking.Patterns.h"//DEBUGNOW

#include "spdlog/spdlog.h"

namespace IHHook {
	extern std::map<std::string, uint64_t> addressSet;
	extern std::map<std::string, uint64_t> hookFuncs;
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


//TODO CULL still in the lua headers, which I can revert/comment out the hooked
#define FUNCPTRDEF(ret, name, ...)\
//

//targetName: name of original function (as exported by ExportInfo) (namespaced as original)
//hookFunc: pointer to your hook function
//static MH_STATUS CreateHook(const char* targetName, LPVOID hookFunc) {
//	uint64_t address = IHHook::addressSet[targetName];
//	if (address == NULL) {
//		spdlog::error("CreateHook: could not fine addressSet[{}]", targetName);
//		return MH_UNKNOWN;
//	}
//
//	MH_STATUS createStatus = MH_CreateHook((LPVOID*)address, hookFunc, (LPVOID*)&name);
//	if (createStatus != MH_OK) {
//		spdlog::error("MH_CreateHook failed, not MH_OK for {}", "foxlua::NewModule");
//	}
//	else {
//		IHHook::hookFuncs[targetName] = (uint64_t)&hookFunc;
//		spdlog::debug("MH_CreateHook MH_OK for {}", "NewModuleHook");
//	}
//	return createStatus;
//}//CreateHook

//targetName: name of original function (as exported by ExportInfo name) (namespaced as original)
//Example use:
//EnableHook("lua::lua_newstate");
static MH_STATUS EnableHook(const char* targetName) {
	uint64_t address = IHHook::addressSet[targetName];
	if (address == NULL) {
		spdlog::error("IHEnableHook: Could not find addressSet[{}]", targetName);
		return MH_UNKNOWN;
	}

	MH_STATUS enableStatus = MH_EnableHook((LPVOID*)address);

	if (enableStatus != MH_OK) {
		spdlog::error("MH EnableHook failed for {} with code {}", targetName, enableStatus);
	}
	else {
		spdlog::debug("MH EnableHook MH_OK for {}", targetName);
	}
	return enableStatus;
}//EnableHook

static MH_STATUS DisableHook(const char* targetName) {
	uint64_t address = IHHook::addressSet[targetName];
	if (address == NULL) {
		spdlog::error("IHEnableHook: Could not find addressSet[{}]", targetName);
		return MH_UNKNOWN;
	}

	MH_STATUS enableStatus = MH_DisableHook((LPVOID*)address);

	if (enableStatus != MH_OK) {
		spdlog::error("MH DisableHook failed for {} with code {}", targetName, enableStatus);
	}
	else {
		spdlog::debug("MH DisableHook MH_OK for {}", targetName);
	}
	return enableStatus;
}//DisableHook

//detour and trampoline via MH_CreateHook,
//original function is at the <name> function ptr (just like createptr)
//while the hook/detour is at <name>Hook function pointer.
//TODO: rethink, could iterate over a map if I have a lookup of name to detour function (name##Hook)
//DEBUGNOW rename CREATE_HOOK_NS to replace this
#define CREATE_HOOK(name)\
if (addressSet[#name]==NULL) {\
	spdlog::error("CREATE_HOOK addressSet[{}]==NULL", #name);\
} else {\
	MH_STATUS name##CreateStatus = MH_CreateHook((LPVOID*)addressSet[#name], name##Hook, (LPVOID*)&name);\
	if (name##CreateStatus != MH_OK) {\
		spdlog::error("MH_CreateHook failed for {} with code {}", #name, name##CreateStatus);\
	} else {\
		spdlog::debug("MH_CreateHook MH_OK for {}", #name);\
	}\
}

//macros still usefull because you can reference the function pointers rather than strings
//and vs intellisense is great these days if you want to know what is actually happening

//Example use:
//CREATE_HOOK_NS(lua::lua_newstate,lua_newstateHook);
//_NS aka NameSpaced (though it can handle non namespaced), or maybe its NewStyle, or is it NinjaShinobi? You decide
#define CREATE_HOOK_NS(name,hookName)\
if (addressSet[#name]==NULL) {\
	spdlog::error("CREATE_HOOK addressSet[{}]==NULL", #name);\
} else {\
	if (MH_CreateHook((LPVOID*)addressSet[#name], hookName, (LPVOID*)&name) != MH_OK) {\
		spdlog::error("MH_CreateHook failed, not MH_OK for {}", #name);\
	} else {\
		spdlog::debug("MH_CreateHook MH_OK for {}", #hookName);\
	}\
}

//see EnableHook
#define ENABLEHOOK(name) EnableHook(#name);

#define DISABLEHOOK(name) DisableHook(#name);

