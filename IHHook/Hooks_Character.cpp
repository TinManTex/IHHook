//tex WIP exploring
// Extending vars.player* character change system
#include "Hooks_Character.h"
#include "spdlog/spdlog.h"
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_Character {
		//UNUSED
		std::map<std::string, uint> PlayerType {
			{"SNAKE",0},
			{"DD_MALE",1},
			{"DD_FEMALE",2},
			{"AVATAR",3},
			{"LIQUID",4},
			{"OCELOT",5},
			{"QUIET",6},
		};

		//GOTCHA: AVATAR player parts not being identical to SNAKE cause the change to fail to load in ACC
		//something to do with 2nd player instance for the 'reflection' i guess
		//does not seem to cause an issue in-mission where there is only the singular player instance

		//[playerType][playerPartsType]=PathCodeExt64.
		std::map<uint, std::map<uint, std::string>> playerPartsFpk = {
			{0,{//SNAKE
					//manual tests
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},//4/MGS1 > ninja test swap
					//{24,"/Assets/tpp/pack/player/parts/plparts_ocelot.fpk"}//24/non existant partsTypeEnum test
				},//MGS snake
			},
			{1,{//DD_MALE
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},
					//{24,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"}
				},//MGS snake
			},
			{2,{}},//DD_FEMALE
			{3,{//AVATAR
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},
					//{24,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"}
				},//MGS snake
			},
			{4,{}},//LIQUID
			{5,{}},//OCELOT
			{6,{}},//QUIET
		};

		std::map<uint, std::map<uint, std::string>> playerPartsParts = {
			{0,{//SNAKE
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},//MGS1 > ninja test swap
					//{284,"/Assets/tpp/parts/chara/ooc/ooc0_main1_def_v00.parts"}//28/non existant partsTypeEnum test
				},//MGS snake
			},
			{1,{//DD_MALE
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},
					//{28,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"}
				},//MGS snake
			},
			{2,{}},//DD_FEMALE
			{3,{//AVAT
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},
					//{28,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"}
				},//MGS snake
			},
			{4,{}},//LIQUID
			{5,{}},//OCELOT
			{6,{}},//QUIET
		};


		//
		//input: uint playerType, uint playerPartsType, string fpkPath
		//REF IH InfMission.UpdateChangeLocationMenu //DEBUGNOW
		int l_SetPlayerPartsFpk(lua_State* L) {
			spdlog::trace(__func__);

			//TODO: validate param types

			uint playerType = (uint)lua_tointeger(L, -3);
			uint playerPartsType = (uint)lua_tointeger(L, -2);
			const char* filePath = lua_tostring(L, -1);

			if (playerType > 255) {
				spdlog::error("l_SetPlayerPartsFpk set playerType > max value of 255");
				return 0;
			}
			if (playerPartsType > 255) {
				spdlog::error("l_SetPlayerPartsFpk set playerPartsType > max value of 255");
				return 0;
			}

			try {
				auto pathsForPlayerType = playerPartsFpk.at(playerType);
				//TODO: log existing path if its being overwritten
				//pathsForPlayerType[playerPartsType] = fpkPath;//tex i guess at is returning a new sub map or something because setting it like this doesnt actually change playerPartsFpk
				playerPartsFpk[playerType][playerPartsType] = std::string(filePath);
				
				spdlog::debug("l_SetPlayerPartsFpk set playerType: {} playerPartsType: {} to {}", playerType, playerPartsType, filePath);
			}
			catch (const std::out_of_range&) {
				spdlog::debug("l_SetPlayerPartsFpk playerPartsFpk could not find for playerType: {}", playerType);
			}

			return 0;
		}//l_SetPlayerPartsFpk
		//REF IH InfMission.UpdateChangeLocationMenu //DEBUGNOW
		int l_SetPlayerPartsPart(lua_State* L) {
			spdlog::trace(__func__);

			//TODO: validate param types

			uint playerType = (uint)lua_tointeger(L, -3);
			uint playerPartsType = (uint)lua_tointeger(L, -2);
			const char* filePath = lua_tostring(L, -1);

			if (playerType > 255) {
				spdlog::error("l_SetPlayerPartsPart set playerType > max value of 255");
				return 0;
			}
			if (playerPartsType > 255) {
				spdlog::error("l_SetPlayerPartsPart set playerPartsType > max value of 255");
				return 0;
			}

			try {
				auto pathsForPlayerType = playerPartsParts.at(playerType);
				//TODO: log existing path if its being overwritten
				playerPartsParts[playerType][playerPartsType] = std::string(filePath);
				spdlog::debug("l_SetPlayerPartsPart set playerType: {} playerPartsType: {} to {}", playerType, playerPartsType, filePath);
			}
			catch (const std::out_of_range&) {
				spdlog::debug("l_SetPlayerPartsPart playerPartsParts could not find for playerType: {}", playerType);
			}

			return 0;
		}//l_SetPlayerPartsPart

		uint64_t* LoadPlayerPartsFpkHook(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
			spdlog::debug("LoadPlayerPartsFpk playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			uint64_t filePath64 = 0;

			//tex see GOTCHA: above
			if (playerType == 3) {
				playerType = 0;
			}

			try {
				auto pathsForPlayerType = playerPartsFpk.at(playerType);
				try {
					auto filePath = pathsForPlayerType.at(playerPartsType);
					filePath64 = PathCode64(filePath.c_str());
					//filePath64 = 0x522a5fbda65be993;
					LoadFile(fileSlotIndex, filePath64);

					return fileSlotIndex;
				}
				catch (const std::out_of_range&) {
					spdlog::debug("LoadPlayerPartsFpkHook pathsForPlayerType could not find for playerPartsType: {}", playerPartsType);
					filePath64 = 0;
				}		
			}
			catch (const std::out_of_range&) {
				spdlog::debug("LoadPlayerPartsFpkHook playerPartsFpk could not find for playerType: {}", playerType);
			}
			//tex fall back to original function
			LoadPlayerPartsFpk(fileSlotIndex, playerType, playerPartsType);
			return fileSlotIndex;
		}//LoadPlayerPartsFpkHook

		uint64_t* LoadPlayerPartsPartsHook(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
			spdlog::debug("LoadPlayerPartsPartsHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			uint64_t filePath64 = 0;

			//tex see GOTCHA: above
			if (playerType == 3) {
				playerType = 0;
			}

			try {
				auto pathsForPlayerType = playerPartsParts.at(playerType);
				try {
					auto filePath = pathsForPlayerType.at(playerPartsType);
					filePath64 = PathCode64(filePath.c_str());
					LoadFile(fileSlotIndex, filePath64);

					return fileSlotIndex;
				}
				catch (const std::out_of_range&) {
					spdlog::debug("LoadPlayerPartsPartsHook pathsForPlayerType could not find for playerPartsType: {}", playerPartsType);
					filePath64 = 0;
				}
			}
			catch (const std::out_of_range&) {
				spdlog::debug("LoadPlayerPartsPartsHook playerPartsParts could not find for playerType: {}", playerType);
			}
			//tex fall back to original function
			LoadPlayerPartsParts(fileSlotIndex, playerType, playerPartsType);
			return fileSlotIndex;
		}//LoadPlayerPartsPartsHook

		//TODO: extend. just vanilla at the moment
		ulonglong* LoadPlayerCamoFpkHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType){
			spdlog::debug("LoadPlayerCamoFpkHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			uint64_t fpkPath = 0;

			if ((playerType == 0) || (playerType == 3)) {//SNAKE, AVATAR
				//ORIG
				if ((20 < playerPartsType - 2) && (playerPartsType < 26)) {
				//playerPartsType - 2 means 0 NORMAL and 1 SCARF will underflow uint playerPartsType to FFFFF/E, 
				//so 20 < is true
				//and then on the other end of the range 23 SWIMWEAR (and above) - 2 == 21 which is 20 <
				//playerPartsType < 26 OCELLOT is current playerPartsType max
				//but after all that, snake/avat don't have swimsuit and just has default fatigues for those entries
				//DEBRAINTEASED
				//if ((playerPartsType < 2) || (playerPartsType > 22 && playerPartsType < 26)) {
					//DEBUGNOW fpkPath = (&SnakeNormalCamoFpkArray_DAT_142a80a10)[(uint64_t)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}

				if (playerPartsType == 7) {//NAKED
					//DEBUGNOW fpkPath = (&SnakeNakedCamoFpkArray_DAT_142a81160)[(uint64_t)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
			}
			else {
				if (playerType == 1) {//DD_MALE
					//DEBUGNOW fpkPath = (&DDMaleCamoFpkArray_DAT_142a818b0)[(uint64_t)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
				if (playerType == 2) {//DD_FEMALE
					//DEBUGNOW fpkPath = (&DDFemaleCamoFpkArray_DAT_142a82000)[(uint64_t)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
			}

			LoadFile(fileSlotIndex, fpkPath);
			return fileSlotIndex;
		}//LoadPlayerCamoFpkHook

		//TODO: extend
		ulonglong* LoadPlayerCamoFv2Hook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
			spdlog::debug("LoadPlayerCamoFpkHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			ulonglong fv2Path = 0;

			if (playerCamoType == 255) {
				LoadFile(fileSlotIndex, 0);
				return fileSlotIndex;
			}
			if ((playerType == 0) || (playerType == 3)) {//SNAKE,AVATAR
				//See LoadPlayerCamoFpk
				if ((playerPartsType < 2) || (playerPartsType > 22 && playerPartsType < 26)) {
					//DEBUGNOW fv2Path = (&SnakeNormalCamoFv2Array_DAT_142a80a18)[(ulonglong)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
				if (playerPartsType == 7) {//NAKED
					//DEBUGNOW fv2Path = (&SnakeNakedCamoFv2Array_DAT_142a81168)[(ulonglong)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
			}
			else {
				if (playerType == 1) {//DD_MALE
					//DEBUGNOW fv2Path = (&DDMaleCamoFv2Array_DAT_142a818b8)[(ulonglong)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
				if (playerType == 2) {//DD_FEMALE
					//DEBUGNOW fv2Path = (&DDFemaleCamoFv2ArrayDAT_142a82008)[(ulonglong)playerCamoType * 2];
					return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
				}
			}

			LoadFile(fileSlotIndex, fv2Path);
			return fileSlotIndex;
		}//LoadPlayerCamoFv2Hook

		//TODO: there's also facialhelispace to deal with before I'm happy with extending this
		ulonglong* LoadPlayerFacialMotionFpkHook(ulonglong* fileSlotIndex, uint playerType){
			spdlog::debug("LoadPlayerFacialMotionFpkHook playerType:{}", playerType);
			if (playerType == 1) {//DD_MALE
				LoadFile(fileSlotIndex, 0x522bba0fe696843e);// /Assets/tpp/pack/player/motion/player2_facial_dd_male.fpk
			}
			else {
				if (playerType == 2) {//DD_FEMALE
					LoadFile(fileSlotIndex, 0x5228819af53ce132);// /Assets/tpp/pack/player/motion/player2_facial_dd_female.fpk
				}
				else {
					if (playerType == 5) {//OCELOT
						LoadFile(fileSlotIndex, 0x522ad6eb108b656a);// /Assets/tpp/pack/player/motion/player2_facial_ocelot.fpk
					}
					else {
						if (playerType == 6) {//QUIET
							LoadFile(fileSlotIndex, 0x522ad26ea9839391);// /Assets/tpp/pack/player/motion/player2_facial_quiet.fpk
						}
						else {//SNAKE,AVATAR (default vanilla), LIQUID
							LoadFile(fileSlotIndex, 0x522a1da4adfd5137);// /Assets/tpp/pack/player/motion/player2_facial_snake.fpk
						}
					}
				}
			}
			return fileSlotIndex;
		}//LoadPlayerFacialMotionFpkHook

		//TODO: extend. just vanilla at the moment
		ulonglong* LoadPlayerFacialMotionMtarHook(ulonglong* fileSlotIndex, int playerType) {
			spdlog::debug("LoadPlayerFacialMotionMtarHook playerType:{}", playerType);
			if (playerType == 1) {
				LoadFile(fileSlotIndex, 0x67026b0d3dfd05e2);// /Assets/tpp/motion/mtar/player2/player2_ddm_facial.mtar
			}
			else {
				if (playerType == 2) {
					LoadFile(fileSlotIndex, 0x670245b34a1d710c);// /Assets/tpp/motion/mtar/player2/player2_ddf_facial.mtar
				}
				else {
					if (playerType == 5) {
						LoadFile(fileSlotIndex, 0x6703e118275df4f2);// /Assets/tpp/motion/mtar/player2/player2_ocelot_facial.mtar
					}
					else {
						if (playerType == 6) {
							LoadFile(fileSlotIndex, 0x6701511616076078);// /Assets/tpp/motion/mtar/player2/player2_quiet_facial.mtar
						}
						else {
							LoadFile(fileSlotIndex, 0x67028b3526a03df4);// /Assets/tpp/motion/mtar/player2/TppPlayer2Facial.mtar
						}
					}
				}
			}
			return fileSlotIndex;
		}//LoadPlayerFacialMotionMtarHook

		//TODO: extend. just vanilla at the moment
		ulonglong* LoadPlayerBionicArmFpkHook(ulonglong* fileSlotIndex, int playerType, uint playerPartsType, uint playerHandType){
			spdlog::debug("LoadPlayerBionicArmFpkHook playerPartsType:{} playerHandType:{}", playerPartsType, playerHandType);
			//SNAKE,AVATAR
			if (((playerType == 0) || (playerType == 3)) && (true)) {//tex NMC uhh why && true
				switch (playerPartsType) {
				case 0://NORMAL
				case 1://NORMAL_SCARF
				case 2://SNEAKING_SUIT
				case 7://NAKED
				case 8://SNEAKING_SUIT_TPP
				case 9://BATTLEDRESS
				case 10://PARASITE
				case 11://LEATHER
				case 12://GOLD
				case 13://SILVER
				case 15://MGS3
				case 16://MGS3_NAKED
				case 17://MGS3_SNEAKING
				case 18://MGS3_TUXEDO
				case 23://SWIMWEAR
				case 24://SWIMWEAR_G
				case 25://SWIMWEAR_H
					//DEBUGNOW LoadFile(fileSlotIndex, (&BionicArmFpkArray_DAT_142a82750)[(ulonglong)playerArmType * 2]);
					LoadPlayerBionicArmFpk(fileSlotIndex, playerType, playerPartsType, playerHandType);
					return fileSlotIndex;
				}
			}
			LoadFile(fileSlotIndex, 0);
			return fileSlotIndex;
		}//LoadPlayerBionicArmFpkHook

		//TODO: extend. just vanilla at the moment
		ulonglong* LoadPlayerBionicArmFv2Hook(ulonglong* fileSlotIndex, int playerType, uint playerPartsType, uint playerHandType) {
			spdlog::debug("LoadPlayerBionicArmFv2Hook playerPartsType:{} playerHandType:{}", playerPartsType, playerHandType);
			//SNAKE,AVATAR
			if (((playerType == 0) || (playerType == 3)) && (true)) {
				switch (playerPartsType) {
				case 0:
				case 1:
				case 2:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 15:
				case 16:
				case 17:
				case 18:
				case 23:
				case 24:
				case 25:
					//DEBUGNOW LoadFile(fileSlotIndex, (&BionicArmFv2Array_DAT_142a82758)[(ulonglong)playerArmType * 2]);
					LoadPlayerBionicArmFv2(fileSlotIndex, playerType, playerPartsType, playerHandType);
					return fileSlotIndex;
				}
			}
			LoadFile(fileSlotIndex, 0);
			return fileSlotIndex;
		}//LoadPlayerBionicArmFv2Hook

		//GOTCHA: since its only called in LoadPlayerPartsSkinToneFv2, so this isnt a hook, just calling this extended version from LoadPlayerPartsSkinToneFv2Hook
		//only called for playerType 1 DD_MALE, 2 DD_FEMALE
		bool CheckPlayerPartsIfShouldApplySkinToneFv2(uint playerType, uint playerPartsType) {
			spdlog::debug("CheckPlayerPartsIfShouldApplySkinToneFv2Hook playerType:{} playerPartsType:{}", playerType, playerPartsType);
			if (true) {
				switch (playerPartsType) {
				case 0://NORMAL
				case 1://NORMAL_SCARF
				case 2://SNEAKING_SUIT
				case 7://NAKED
				case 8://SNEAKING_SUIT_TPP
				case 9://BATTLEDRESS
				case 11://LEATHER
				case 12://GOLD
				case 13://SILVER
				case 14://AVATAR_EDIT_MAN
				case 15://MGS3
				case 16://MGS3_NAKED
				case 17://MGS3_SNEAKING
				case 18://MGS3_TUXEDO
				case 19://EVA_CLOSE
				case 20://EVA_OPEN
				case 21://BOSS_CLOSE
				case 22://BOSS_OPEN
				case 23://SWIMWEAR
				case 24://SWIMWEAR_G
				case 25://SWIMWEAR_H
					if (playerType == 1) {//DD_MALE
						if (playerPartsType != 17) {//MGS3_SNEAKING
							return true;
						}
					}
					else if (playerType == 2) {//DD_FEMALE
						if (playerPartsType != 21) {//BOSS_CLOSE
							return true;
						}
					} else {//tex not hit in vanilla
						return true;
					}
				}//switch
			}
			return false;
		}//CheckPlayerPartsIfShouldApplySkinToneFv2

		//tex these fv2s are in the playerparts fpk VERIFY
		//TODO: expand. fill out all the data taking CheckPlayerPartsIfShouldApplySkinToneFv2 into account 
		//then assume if value then apply and CheckPlayerPartsIfShouldApplySkinToneFv2 will no longer be nessesary
		//TODO: figure out how AVATAR is handled, inital look at LoadPlayerFv2s it doesnt seem to use this for AVAT, then what is its skin tone situation?
		ulonglong* LoadPlayerPartsSkinToneFv2Hook(ulonglong* loadFile, uint playerType, uint playerPartsType) {
			spdlog::debug("LoadPlayerPartsSkinToneFv2Hook playerType:{} playerPartsType:{}", playerType, playerPartsType);
			bool shouldApplySkinToneFv2 = false;
			ulonglong fv2Path = 0;

			if (playerType == 0) {//SNAKE
				if (playerPartsType == 18) {//MGS3_TUXEDO
					fv2Path = 0x608961e868491c54;////"/Assets/tpp/fova/chara/dld/dld0_main0_sna.fv2";
				}
			} else if (playerType == 1) {//DD_MALE
				shouldApplySkinToneFv2 = CheckPlayerPartsIfShouldApplySkinToneFv2(playerType, playerPartsType);
				if (shouldApplySkinToneFv2) {
					switch (playerPartsType) {
					case 8://SNEAKING_SUIT_TPP
						fv2Path = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
						break;
					case 9://BATTLEDRESS
						fv2Path = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
						break;
					case 15://MGS3
						fv2Path = 0x608b3a2e8398415b;// "/Assets/tpp/fova/chara/dla/dla0_plym0_v00.fv2";
						break;
					case 16://MGS3_NAKED
						fv2Path = 0x608bed35c90a314d;// "/Assets/tpp/fova/chara/dla/dla1_plym0_v00.fv2";
						break;
					case 18://MGS3_TUXEDO
						fv2Path = 0x608872bab5e53bc8; // "/Assets/tpp/fova/chara/dld/dld0_plym0_v00.fv2";
						break;
					case 23://SWIMWEAR
						fv2Path = 0x608aa0de59bf9572; // "/Assets/tpp/fova/chara/dlf/dlf1_main0_v00.fv2";
						break;
					case 24://SWIMWEAR_G
						fv2Path = 0x6088dd7cacaa3fd6; // "/Assets/tpp/fova/chara/dlg/dlg1_main0_v00.fv2";
						break;
					case 25://SWIMWEAR_H
						fv2Path = 0x60884821796ed8f0;// "/Assets/tpp/fova/chara/dlh/dlh1_main0_v00.fv2";
						break;
					default:
						fv2Path = 0x608882ccbb15c7ab;//"/Assets/tpp/fova/chara/sna/dds5_main0_ply_v00.fv2"
						break;
					}//switch(playerPartsType)
				}//shouldApplySkinToneFv2
			} else if (playerType == 2) {
				shouldApplySkinToneFv2 = CheckPlayerPartsIfShouldApplySkinToneFv2(playerType, playerPartsType);
				if (shouldApplySkinToneFv2) {
					switch (playerPartsType) {
					case 8://SNEAKING_SUIT_TPP
						fv2Path = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
						break;
					case 9://BATTLEDRESS
						fv2Path = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
						break;
					case 19://EVA_CLOSE
						fv2Path = 0x608bc54842becde0;// "/Assets/tpp/fova/chara/dle/dle0_plyf0_v00.fv2";
						break;
					case 20://EVA_OPEN
						fv2Path = 0x608a91e3d60c5980;// "/Assets/tpp/fova/chara/dle/dle1_plyf0_v00.fv2";
						break;
					case 22://BOSS_OPEN
						fv2Path = 0x6089e156b2cacad9;// "/Assets/tpp/fova/chara/dlc/dlc1_plyf0_v00.fv2";
						break;
					case 23://SWIMWEAR
						fv2Path = 0x6088fc6455404f89;// "/Assets/tpp/fova/chara/dlf/dlf1_main0_f_v00.fv2";
						break;
					case 24://SWIMWEAR_G
						fv2Path = 0x6089659d7ee7f080;// "/Assets/tpp/fova/chara/dlg/dlg1_main0_f_v00.fv2";
						break;
					case 25://SWIMWEAR_H
						fv2Path = 0x6089e8ede46843e9; // "/Assets/tpp/fova/chara/dlh/dlh1_main0_f_v00.fv2";
						break;
					default:
						fv2Path = 0x608a1c34fefc05c2;// "/Assets/tpp/fova/chara/sna/dds6_main0_ply_v00.fv2";
						break;
					}//switch(playerPartsType)
				}//shouldApplySkinToneFv2
			}//if playerType

			LoadFile(loadFile, fv2Path);
			return loadFile;
		}//LoadPlayerPartsSkinToneFv2Hook

		//TODO: 
		bool IsHeadNeededForPartsTypeAndAvatarHook(uint playerPartsType){
			if (true) {
				switch (playerPartsType) {
				case 0:
				case 1:
				case 2:
				case 7:
				case 8:
				case 9:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
					return true;
				}
			}
			//?
			if (playerPartsType == 3) {
				return true;
			}
			return false;
		}//IsHeadNeededForPartsTypeAndAvatarHook

		//TODO: LoadPlayerSnakeFaceFpk

		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(LoadPlayerPartsFpk)
			CREATE_HOOK(LoadPlayerPartsParts)
			CREATE_HOOK(LoadPlayerCamoFpk)
			CREATE_HOOK(LoadPlayerCamoFv2)
			CREATE_HOOK(LoadPlayerBionicArmFpk)
			CREATE_HOOK(LoadPlayerBionicArmFv2)
			CREATE_HOOK(LoadPlayerFacialMotionFpk)
			CREATE_HOOK(LoadPlayerFacialMotionMtar)
			CREATE_HOOK(LoadPlayerPartsSkinToneFv2)
				
			ENABLEHOOK(LoadPlayerPartsFpk)
			ENABLEHOOK(LoadPlayerPartsParts)
			ENABLEHOOK(LoadPlayerCamoFpk)
			ENABLEHOOK(LoadPlayerCamoFv2)
			ENABLEHOOK(LoadPlayerBionicArmFpk)
			ENABLEHOOK(LoadPlayerBionicArmFv2)
			ENABLEHOOK(LoadPlayerFacialMotionFpk)
			ENABLEHOOK(LoadPlayerFacialMotionMtar)
			ENABLEHOOK(LoadPlayerPartsSkinToneFv2)
		}//CreateHooks
	}//Hooks_Character
}//namespace IHHook