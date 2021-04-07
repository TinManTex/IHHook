#include "Hooks_TPP.h"
#include "IHHook.h"//BaseAddr
#include "spdlog/spdlog.h"

#include "MinHook/MinHook.h"
#include "HookMacros.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>   

namespace IHHook {
	//DEBUGNOW push this into somewhere more accessable
	FUNC_DECL_ADDR(StrCode64)
	FUNC_DECL_SIG(StrCode64, 
		"\x48\x89\x00\x00\x00\x56\x48\x83\xEC\x00\x80\x3C\x0A", 
		"xx???xxxx?xxx")
	FUNC_DECL_PATTERN(StrCode64, "48 89 ? ? ? 56 48 83 EC ? 80 3C 0A")

	std::map<int, long long> locationLangIds{
		{10,0x1b094033d45d},//afgh,tpp_loc_afghan
		{20,0x7114b69e71e7},//mafr,tpp_loc_africa
		{50,0xfa8eaa7758b1},//mtbs,tpp_loc_mb

		//DEBUGNOW proof of concept hack
		//{40,0x27376b6e62ff},//tpp_loc_gntn - caplags langid from his gntn addon
	};

	namespace Hooks_TPP {
		uintptr_t missionCode_Addr = 0x142A58A00;
		//uint32_t* missionCode;//tex in header

		FUNCPTRDEF(void, UnkSomePlayerUpdateFunc, uintptr_t unkPlayerClass, uintptr_t playerIndex)
		FUNC_DECL_ADDR(UnkSomePlayerUpdateFunc)
		
		void UnkSomePlayerUpdateFuncHook(intptr_t unkPlayerClass, uintptr_t playerIndex) {
			spdlog::trace(__func__);
			UnkSomePlayerUpdateFunc(unkPlayerClass, playerIndex);

			intptr_t playerClass = unkPlayerClass;
			
		}//UnkSomePlayerUpdateFuncHook

		FUNCPTRDEF(long long*, GetFreeRoamLangId, long long* langId, short locationCode, short missionCode);
		FUNC_DECL_ADDR(GetFreeRoamLangId)
		FUNC_DECL_SIG(GetFreeRoamLangId,
			"\x0F\xB7\x00\x83\xF8\x00\x74\x00\x83\xF8\x00\x74\x00\x83\xF8\x00\x74\x00\x48\xB8",
			"xx?xx?x?xx?x?xx?x?xx")
		FUNC_DECL_PATTERN(GetFreeRoamLangId,"0F B7 ? 83 F8 ? 74 ? 83 F8 ? 74 ? 83 F8 ? 74 ? 48 B8")

		//tex the idroid free roam mission tab had an issue where it wouldn't show the name of custom free roam missions
		//despite there being a map_location_parameter - locationNameLangId = "tpp_loc_<whatever> (that matches tpp_common lng for vanilla free)
		//however the above map does show
		//given that there's a location icon I guess that's set up in engine
		//See IH InfMission.EnableLocationChangeMissions
		//searching for the hashes of the mentioned tpp_loc<> (kept for ref) in the exe finds this function
		//returns strcode64
		//IN: locationLangIds
		long long* GetFreeRoamLangIdHook(long long* langId, short locationCode, short missionCode) {
			spdlog::trace(__func__);

			//DEBUGNOW only missionCode entry in vanilla
			if (missionCode == 30150) {//mtbs_zoo
				*langId = 0xe3d47a6e1e15;//tpp_loc_mb_zoo
				return langId;
			}

			auto iterator = locationLangIds.find(locationCode);
			if (iterator != locationLangIds.end()) {
				*langId = iterator->second;//value
				return langId;
			}

			//if (locationCode == 10) {//afgh
			//	*langId = 0x1b094033d45d;////tpp_loc_afghan
			//	return langId;
			//}
			//if (locationCode == 20) {//mafr
			//	*langId = 0x7114b69e71e7;
			//	return langId;
			//}
			//if (locationCode == 50) {//mtbs
			//	*langId = 0xfa8eaa7758b1;//tpp_loc_mb 
			//	return langId;
			//}


			////DEBUGNOW proof of concept hack
			//if (locationCode == 40) {//gntn
			//	*langId = 0x27376b6e62ff;//tpp_loc_gntn - caplags langid from his gntn addon
			//	return langId;
			//}
			
			*langId = 0xb8a0bf169f98;// "" empty string
			return langId;
		}//GetFreeRoamLangIdHook

		void CreateHooks(size_t RealBaseAddr) {
			spdlog::trace(__func__);
			//DEBUGNOW hitting some kind of exception on caps machine
			//missionCode = NULL;
			//try {
			//	missionCode = (uint32_t*)((missionCode_Addr - BaseAddr) + RealBaseAddr);
			//}
			//catch (std::runtime_error & e) {
			//	spdlog::error("CHP: runtime exception - {}", e.what());
			//	auto log = spdlog::get("ihhook");
			//	log->flush();
			//}
			//if (missionCode==NULL) {
			//	spdlog::error("CHP: missionCode==NULL");
			//}
			//DEBUGNOW

			if (isTargetExe) {
				GET_REBASED_ADDR(StrCode64)
			}
			else {
				GET_SIG_ADDR(StrCode64)
			}
			if (StrCode64Addr == NULL) {
				spdlog::warn("addr fail: StrCode64Addr == NULL");
			}
			else {
				CREATE_FUNCPTR(StrCode64)			
					
				//DEBUGNOW TEST
				const char* langId = "tpp_loc_afghan";
				long long tpp_loc_afghanS64 = StrCode64(langId, strlen(langId));

				std::stringstream stream;
				stream << std::hex << tpp_loc_afghanS64;
				std::string result(stream.str());
				spdlog::debug("Str64 tpp_loc_afghan:0x{}", result);

				//0x1b094033d45d//tpp_loc_afghan
					//{ 20,0x7114b69e71e7 },//mafr,tpp_loc_africa
					//{ 50,0xfa8eaa7758b1 },//mtbs,tpp_loc_mb
					////DEBUGNOW proof of concept hack
					//{ 40,0x27376b6e62ff },//tpp_loc_gntn - caplags langid from his gntn addon
			}


	
			if (isTargetExe) {
				GET_REBASED_ADDR(GetFreeRoamLangId)
			}
			else {
				GET_SIG_ADDR(GetFreeRoamLangId)
			}
			if (GetFreeRoamLangIdAddr == NULL) {
				spdlog::warn("addr fail: GetFreeRoamLangIdAddr == NULL");
			}
			else {
				CREATE_HOOK(GetFreeRoamLangId)
				ENABLEHOOK(GetFreeRoamLangId)
			}

			//DEBUGNOW
			//CREATE_HOOK(UnkSomeUpdateFunc)
			//ENABLEHOOK(UnkSomeUpdateFunc)
		}//CreateHooks
	}//Hooks_TPP
}//namespace IHHook