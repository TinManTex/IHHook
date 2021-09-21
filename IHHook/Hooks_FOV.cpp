// adapted from //mons fork of AltimoorTADSKs fov Modifier dll https://github.com/mon/MGSV-TPP-FoV
// supported by IH InfCamHook.lua

#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <filesystem>//exename

#include "spdlog/spdlog.h"
#include "MinHook.h"
#include "HookMacros.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <MemoryUtils.h>

#include "IHHook.h"//DEBUGNOW
#include "mgsvtpp_func_typedefs.h"

namespace IHHook {
	namespace Hooks_FOV {
		FUNC_DECL_ADDR(UpdateFOVLerp)

		enum class gametype { mgsv, mgo };

		gametype game = gametype::mgsv;

		enum CamMode {
			NORMAL,
			AIMING,
			HIDING,
			CQC,
		};

		//DEBUGNOW TODO: rename focal length
		//NMC fov is in focal length of a 24mm x 36mm camera lens and is locked horizontally
		const auto default_tpp_fov = 21.F;
		const auto default_shoulder_fov = 22.F;
		const auto default_hiding_fov = 26.F;
		const auto default_cqc_fov = 32.F;
		//DEBUGNOW
		//fpv is per scope type I think
		//but then sniper rifles have multi zoom, but they dont use sepetate focal length (all 42).
		const auto default_fpv_scope1_fov = 29.F;
		const auto default_fpv_scope2_fov = 42.F;

		bool enableFovHook = false;
		float new_tpp_fov = default_tpp_fov;
		float new_shoulder_fov = default_shoulder_fov;
		float new_hiding_fov = default_hiding_fov;
		float new_cqc_fov = default_cqc_fov;

		/**
		 * hook_update_fov_lerp - Change the target fov
		 * @thisptr:	Struct containing fov data
		 *
		 * Check the unmodified focal length and change to the appropriate new one
		 */
		void __fastcall UpdateFOVLerpHook(const uintptr_t thisptr) {
			auto* target_focalLength = (float*)(thisptr + (game == gametype::mgo ? 0x2EC : 0x2FC));
			//spdlog::trace("target_fov:{}",*target_focalLength);//DEBUGNOW
			//DEBUGNOW crude, need a better way of idenifying what focalLength is being set
			*target_focalLength =
				*target_focalLength == default_tpp_fov ? new_tpp_fov :
				*target_focalLength == default_shoulder_fov ? new_shoulder_fov :
				*target_focalLength == default_hiding_fov ? new_hiding_fov :
				*target_focalLength == default_cqc_fov ? new_cqc_fov :
				*target_focalLength;

			UpdateFOVLerp(thisptr);
		}//UpdateFOVLerpHook

		const auto deg2rad = 3.1415926F / 180.F;
		const auto frame_width = 36.F;
		//ex new_tpp_fov =  (90, default_tpp_fov, default_tpp_fov)
		//ex new_shoulder_fov =  (90, default_tpp_fov, default_shoulder_fov)
		//NMC fov is in focal length of a 24mm x 36mm camera lens and is locked horizontally
		//fov in degrees to focalLength, ex 90,100
		float CalculateFocalLength(float fov, float defaultFocalLength, float defaultModeFocalLength) {
			const auto fov_tan = tan(fov * deg2rad / 2.F);
			//REF CULL
			//new_tpp_fov = frame_width / tpp_fov_tan / 2.F;
			//new_shoulder_fov = frame_width / (tpp_fov_tan * (default_tpp_fov / default_shoulder_fov)) / 2.F;
			//new_hiding_fov = frame_width / (tpp_fov_tan * (default_tpp_fov / default_hiding_fov)) / 2.F;
			//new_cqc_fov = frame_width / (tpp_fov_tan * (default_tpp_fov / default_cqc_fov)) / 2.F;

			float newFocalLength = frame_width / (fov_tan * (defaultFocalLength / defaultModeFocalLength)) / 2.F;
			return newFocalLength;
		}//CalculateFocalLength

		void CreateHooks(size_t RealBaseAddr) {
			HMODULE hExe = GetModuleHandle(NULL);
			WCHAR fullPath[MAX_PATH]{ 0 };
			GetModuleFileNameW(hExe, fullPath, MAX_PATH);
			std::filesystem::path path(fullPath);
			std::wstring exeName = path.filename().c_str();
			if (exeName.find(L"mgo") != std::wstring::npos) {
				game = gametype::mgo;
			}
			//DEBUGNOW CULL
			//std::ifstream config("fov.cfg");
			//float tpp_fov;
			//config >> tpp_fov;

			////NMC fov is in focal length of a 24mm x 36mm camera lens and is locked horizontally
			//const auto deg2rad = 3.1415926F / 180.F;
			//const auto frame_width = 36.F;
			//const auto tpp_fov_tan = tan(tpp_fov * deg2rad / 2.F);
			//new_tpp_fov = CalculateFocalLength(tpp_fov, default_tpp_fov, default_tpp_fov);
			//new_shoulder_fov = CalculateFocalLength(tpp_fov, default_tpp_fov, default_shoulder_fov);
			//new_hiding_fov = CalculateFocalLength(tpp_fov, default_tpp_fov, default_hiding_fov);
			//new_cqc_fov = CalculateFocalLength(tpp_fov, default_tpp_fov, default_cqc_fov);

			// NMC: the game doesn't have the encryption routines, just run the hook
			// eg update 1.14
			// tex unless konami goes crazy and reenables encryption (in that case refer to the original fov hook), just assuming it will stay off.

			//tex as far as I can tell sig is some point before the actual ref it wants, why? dont know.
			//the actual reference is a relative pointer as part of a call to the actual function we want

			//REF: E8 cd 	CALL rel32 	Call near, relative, displacement relative to next instruction
			//14111dc7f e8 7c 8b ff ff
			//updateFOVLerpRef = 14111dc80 > 7c 8b
			//const auto updateFOVLerpRef = (int32_t*)(MemoryUtils::sigscan("updateFOVLerpRef",
			//	"\x48\x8B\x8F\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x48\x8D\x4F\xE0\xE8",
			//	"xxx????xxxxxxxxxxx") + 18);

			//if (updateFOVLerpRef == NULL){
			//	spdlog::warn("FOV hook fail: update_fov_lerp_ref == NULL");
			//	return;
			//}

			//tex update_fov_lerp() 1.0.15.3 = 0x141116800, in case the unlikely event sig breaks
			//tex since updateFOVLerpRef is at the address part of of the E8 CALL rel32 (see REF above again), it needs to jump to the next instruction (+4)
			//then add the dereferenced rel32
			//UpdateFOVLerpAddr = ((intptr_t)(updateFOVLerpRef)+ptrdiff_t(4)) + *updateFOVLerpRef;

			if (addressSet["UpdateFOVLerp"] == NULL) {
				spdlog::warn("FOV addr fail: UpdateFOVLerpAddr == NULL");
				return;
			}

			CREATE_HOOK(UpdateFOVLerp)
			//DEBUGNOW ENABLEHOOK(UpdateFOVLerp)
		}//CreateHooks

		void SetFocalLength(CamMode camMode, float focalLength) {
			switch (camMode) {
				case CamMode::NORMAL:
					new_tpp_fov = focalLength;
					break;
				case CamMode::AIMING:
					new_shoulder_fov = focalLength;
					break;
				case CamMode::HIDING:
					new_hiding_fov = focalLength;
					break;
				case CamMode::CQC:
					new_cqc_fov = focalLength;
					break;
			default:
				break;
			}
		}//SetFocalLength

		int l_SetCamHook(lua_State* L) {
			spdlog::trace(__func__);
			if (lua_type(L, -1) != LUA_TNUMBER) {
				spdlog::warn("SetCamHook expects integer 0,1");
				return 0;
			}

			int enable = (int)lua_tointeger(L, -1);
			if (enable == 0) {
				new_tpp_fov = default_tpp_fov;
				new_shoulder_fov = default_shoulder_fov;
				new_hiding_fov = default_hiding_fov;
				new_cqc_fov = default_cqc_fov;
				DISABLEHOOK(UpdateFOVLerp);
			}
			else {
				ENABLEHOOK(UpdateFOVLerp)
			}
			return 0;
		}//l_SetCamHook

		int l_UpdateCamHook(lua_State* L) {
			spdlog::trace(__func__);
			if (lua_type(L, -2) != LUA_TNUMBER) {
				spdlog::warn("SetCamHook expects integer camMode Enum");
				return 0;
			}
			if (lua_type(L, -1) != LUA_TNUMBER) {
				spdlog::warn("SetCamHook expects float focalLength");
				return 0;
			}

			CamMode camMode = (CamMode)lua_tointeger(L, -2);
			float focalLength = (float)lua_tonumber(L, -1);
			SetFocalLength(camMode, focalLength);
			return 0;
		}//l_UpdateCamHook
	}//namespace Hooks_FOV
}//namespace IHHook