#include "Hooks_TPP.h"
#include "IHHook.h"//BaseAddr
#include "spdlog/spdlog.h"

#include "MinHook/MinHook.h"
#include "HookMacros.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>   
#include "mgsvtpp_func_typedefs.h"

//tex DEBUGNOW figure out scope issues with using this (LuaIHH), the extern func pointers are declared with no scope (which is what lua wants)
FUNC_DECL_ADDR(StrCode64)

namespace IHHook {
	std::map<int, long long> locationLangIds{
		{10,0x1b094033d45d},//afgh,tpp_loc_afghan
		{20,0x7114b69e71e7},//mafr,tpp_loc_africa
		{50,0xfa8eaa7758b1},//mtbs,tpp_loc_mb

		//DEBUGNOW proof of concept hack
		//{40,0x27376b6e62ff},//tpp_loc_gntn - caplags langid from his gntn addon
	};

	namespace Hooks_TPP {
		//tex from here
		//https://discord.com/channels/364177293133873153/364178190588968970/698650439817625691
		//(though still not sure how partoftheworlD recognised this in the first place)
		//If you memory dump the exe after execution of this point ghidra recognises this as entry point in the dumped exe
		//eyeballing the function it seems to be _mainCRTStartup
		//https://stackoverflow.com/questions/22934206/what-is-the-difference-between-main-and-maincrtstartup
		//"mainCRTStartup basically looks like this: 
		//init_tls(); 
		//init_crt(); 
		//run_global_constructors(); 
		//get_args(&argc, &argv); 
		//ret = main(argc, argv); 
		//run_global_destructors(); 
		//exit(ret); 
		//.So, main is in there, some place.– Damon Apr 8 '14 at 11:03"
		//tex so you can find actual main from this
		//not much point hooking it or actual main (lets call it FoxMain to be clearer) at the moment since IHHook is currently a dinput8 proxy which is obviously well past the _crtMain/FoxMain execute point
		//FUNC_DECL_ADDR(_mainCRTStartup)


		uintptr_t missionCode_Addr = 0x142A58A00;
		//uint32_t* missionCode;//tex in header

		//TODO: move to exploration
		//FUNC_DECL_ADDR(UnkSomePlayerUpdateFunc)//DEBUGNOW re-find, export in cvs and dump sig - 0x146e3a620 what ver was this from? 15.1,  0x146900690 = 15.3 DEBUGNOW

		//void UnkSomePlayerUpdateFuncHook(intptr_t unkPlayerClass, uintptr_t playerIndex) {
		//	spdlog::trace(__func__);
		//	UnkSomePlayerUpdateFunc(unkPlayerClass, playerIndex);

		//	intptr_t playerClass = unkPlayerClass;
		//	
		//}//UnkSomePlayerUpdateFuncHook

		////Address of signature = mgsvtpp_1_0_15_1_en.exe + 0x012C7570//15.1
		//FUNC_DECL_ADDR(UnkAnotherPlayerUpdateFuncButHuge)// 0x1412cf110 = 15.3 DEBUGNOW

		
			
	


		FUNC_DECL_ADDR(GetFreeRoamLangId)

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

	

		FUNC_DECL_ADDR(UnkSomePrintFunction)

		//DEBUGNOW not really tpp only Hooks_Fox?
		static void UnkSomePrintFunctionHook(char* fmt, ...) {
			spdlog::trace(__func__);
			va_list args;
			va_start(args, fmt);

			int size = 100;
			std::string message;
			va_list ap;

			while (1) {
				message.resize(size);
				va_start(ap, fmt);
				int n = vsnprintf(&message[0], size, fmt, ap);
				va_end(ap);

				if (n > -1 && n < size) {
					message.resize(n); // Make sure there are no trailing zero char
					break;
				}
				if (n > -1)
					size = n + 1;
				else
					size *= 2;
			}//while(1)


			spdlog::debug(message);
		}//UnkSomePrintFunctionHook

		FUNC_DECL_ADDR(nullsub_2)
		void nullsub_2Hook(char* unkSomeIdStr, unsigned long long unkSomeIdNum) {
			//spdlog::trace(__func__);
			if (unkSomeIdStr != NULL) {
				try {
					char idStr[1024];
					sprintf(idStr, "%s", unkSomeIdStr);
					spdlog::debug("nullsub_2 {}", idStr);
				}
				catch(...)  {

				}
			}
		}//nullsub_2Hook

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

			//DEBUGNOW
			//if (_mainCRTStartupAddr == NULL) {
			//	bool bleh = true;
			//}

			if (addressSet["StrCode64"] == NULL) {
				spdlog::warn("addr fail: addressSet[\"StrCode64\"] == NULL");
			}
			else {
				CREATE_FUNCPTR(StrCode64)			
					
				//DEBUGNOW TEST
				char* langId = "tpp_loc_afghan";
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

			if (addressSet["GetFreeRoamLangId"] == NULL
				|| addressSet["UnkSomePrintFunction"] == NULL
				|| addressSet["nullsub_2"] == NULL
			) {
				spdlog::warn("addr == NULL");
			}
			else {
				CREATE_HOOK(GetFreeRoamLangId)
				CREATE_HOOK(UnkSomePrintFunction)
				CREATE_HOOK(nullsub_2)

				ENABLEHOOK(GetFreeRoamLangId)

				ENABLEHOOK(UnkSomePrintFunction)//DEBUGNOW
#ifdef _DEBUG
				//ENABLEHOOK(nullsub_2)//DEBUGNOW
#endif // DEBUG
			}//if addr

			//DEBUGNOW
			//CREATE_HOOK(UnkSomeUpdateFunc)
			//ENABLEHOOK(UnkSomeUpdateFunc)
		}//CreateHooks
	}//Hooks_TPP
}//namespace IHHook