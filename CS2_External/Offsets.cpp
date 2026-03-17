#include "Offsets.h"
#include <string>
#include <fstream>
#include <sstream>
#include "yaml-cpp/yaml.h"
#include <iostream>
#include "resource.h"

// Helper to handle mixed hex/decimal from yaml
template<typename T>
T get_val(const YAML::Node& n) {
    if (!n.IsDefined() || n.IsNull()) return 0;
    std::string s = n.as<std::string>();
    if (s.empty()) return 0;
    
    try {
        // Check if it's hex (prefixed with 0x)
        if (s.find("0x") == 0 || s.find("0X") == 0)
            return (T)std::stoul(s, nullptr, 16);
        
        // If it contains A-F and no other weird chars, it's likely hex even without 0x
        bool has_hex_chars = false;
        for(char c : s) {
            if (isxdigit(c) && !isdigit(c)) {
                has_hex_chars = true;
                break;
            }
        }
        
        if (has_hex_chars)
            return (T)std::stoul(s, nullptr, 16);
        else
            return (T)std::stoull(s, nullptr, 10); // Use stoull for large decimals
            
    } catch (...) {
        return (T)0;
    }
}

bool Offset::UpdateOffsets()
{
    YAML::Node config;
    try {
        std::string yamlPath = "offsets.yaml";
        bool loaded = false;
        
        // 1. Try to load from file (for development/updates)
        std::ifstream f(yamlPath);
        if (!f.good()) {
            yamlPath = "../offsets.yaml";
            f.open(yamlPath);
        }
        
        if (f.good()) {
            config = YAML::Load(f);
            std::cout << "[Info] Loaded offsets from file: " << yamlPath << std::endl;
            loaded = true;
        }
        f.close();

        // 2. Fallback: Load from resource (embedded in exe)
        if (!loaded) {
            HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_OFFSETS_YAML), RT_RCDATA);
            if (hRes) {
                HGLOBAL hData = LoadResource(NULL, hRes);
                if (hData) {
                    DWORD dataSize = SizeofResource(NULL, hRes);
                    char* data = (char*)LockResource(hData);
                    if (data) {
                        std::string content(data, dataSize);
                        config = YAML::Load(content);
                        std::cout << "[Info] Loaded offsets from embedded resource." << std::endl;
                        loaded = true;
                    }
                }
            }
        }

        if (!loaded) {
            std::cout << "[ERROR] Could not find offsets.yaml or load embedded resource." << std::endl;
            return false;
        }

        auto client = config["client_dll"];
        auto engine = config["engine2_dll"];
        auto input = config["inputsystem_dll"];
        auto classes = client["classes"];

        // Global Offsets
        Offset::EntityList = get_val<DWORD>(client["dwEntityList"]);
        Offset::LocalPlayerController = get_val<DWORD>(client["dwLocalPlayerController"]);
        Offset::LocalPlayerPawn = get_val<DWORD>(client["dwLocalPlayerPawn"]);
        Offset::GlobalVars = get_val<DWORD>(client["dwGlobalVars"]);
        Offset::ViewAngle = get_val<DWORD>(client["dwViewAngles"]);
        Offset::Matrix = get_val<DWORD>(client["dwViewMatrix"]);
        Offset::PlantedC4 = get_val<DWORD>(client["dwPlantedC4"]);
        Offset::Sensitivity = get_val<DWORD>(client["dwSensitivity"]);
        Offset::InputSystem = get_val<DWORD>(input["dwInputSystem"]);
        Offset::ForceJump = get_val<DWORD>(client["jump"]);
        Offset::ForceCrouch = get_val<DWORD>(client["duck"]);
        Offset::ForceForward = get_val<DWORD>(client["forward"]);
        Offset::ForceLeft = get_val<DWORD>(client["left"]);
        Offset::ForceRight = get_val<DWORD>(client["right"]);

        // Entity Offsets
        auto baseEntity = classes["C_BaseEntity"]["fields"];
        auto playerController = classes["CCSPlayerController"]["fields"];
        
        Offset::Entity.Health = get_val<DWORD>(playerController["m_iPawnHealth"]);
        Offset::Entity.TeamID = get_val<DWORD>(baseEntity["m_iTeamNum"]);
        Offset::Entity.IsAlive = get_val<DWORD>(playerController["m_bPawnIsAlive"]);
        Offset::Entity.PlayerPawn = get_val<DWORD>(playerController["m_hPawn"]);
        Offset::Entity.iszPlayerName = get_val<DWORD>(playerController["m_iszPlayerName"]);

        // Pawn Offsets
        auto basePawn = classes["C_BasePlayerPawn"]["fields"];
        auto csPawn = classes["C_CSPlayerPawn"]["fields"];
        
        Offset::Pawn.MovementServices = get_val<DWORD>(basePawn["m_pMovementServices"]);
        Offset::Pawn.WeaponServices = get_val<DWORD>(basePawn["m_pWeaponServices"]);
        Offset::Pawn.BulletServices = get_val<DWORD>(csPawn["m_pBulletServices"]);
        Offset::Pawn.CameraServices = get_val<DWORD>(basePawn["m_pCameraServices"]);
        Offset::Pawn.pClippingWeapon = get_val<DWORD>(csPawn["m_pClippingWeapon"]);
        
        Offset::Pawn.Pos = get_val<DWORD>(basePawn["m_vOldOrigin"]);
        Offset::Pawn.MaxHealth = get_val<DWORD>(baseEntity["m_iMaxHealth"]);
        Offset::Pawn.CurrentHealth = get_val<DWORD>(baseEntity["m_iHealth"]);
        Offset::Pawn.GameSceneNode = get_val<DWORD>(baseEntity["m_pGameSceneNode"]);
        Offset::Pawn.angEyeAngles = get_val<DWORD>(csPawn["m_angEyeAngles"]);
        Offset::Pawn.vecLastClipCameraPos = get_val<DWORD>(csPawn["m_vecLastClipCameraPos"]);
        Offset::Pawn.iShotsFired = get_val<DWORD>(csPawn["m_iShotsFired"]);
        Offset::Pawn.flFlashMaxAlpha = get_val<DWORD>(csPawn["m_flFlashMaxAlpha"]);
        Offset::Pawn.flFlashDuration = get_val<DWORD>(csPawn["m_flFlashDuration"]);
        Offset::Pawn.aimPunchAngle = get_val<DWORD>(csPawn["m_aimPunchAngle"]);
        Offset::Pawn.aimPunchCache = get_val<DWORD>(csPawn["m_aimPunchCache"]);
        Offset::Pawn.iIDEntIndex = get_val<DWORD>(csPawn["m_iIDEntIndex"]);
        Offset::Pawn.iTeamNum = get_val<DWORD>(baseEntity["m_iTeamNum"]);
        Offset::Pawn.fFlags = get_val<DWORD>(baseEntity["m_fFlags"]);

        auto camServices = classes["CPlayer_CameraServices"]["fields"];
        Offset::Pawn.iFovStart = get_val<DWORD>(camServices["m_iFOVStart"]);

        auto spottedState = classes["EntitySpottedState_t"]["fields"];
        Offset::Pawn.bSpottedByMask = get_val<DWORD>(csPawn["m_entitySpottedState"]) + get_val<DWORD>(spottedState["m_bSpottedByMask"]);

        // PlayerController Offsets
        Offset::PlayerController.m_hPawn = get_val<DWORD>(playerController["m_hPawn"]);
        Offset::PlayerController.m_pObserverServices = get_val<DWORD>(basePawn["m_pObserverServices"]);
        Offset::PlayerController.m_hObserverTarget = get_val<DWORD>(classes["CPlayer_ObserverServices"]["fields"]["m_hObserverTarget"]);
        Offset::PlayerController.m_hController = get_val<DWORD>(basePawn["m_hController"]);
        Offset::PlayerController.PawnArmor = get_val<DWORD>(playerController["m_iPawnArmor"]);
        Offset::PlayerController.HasDefuser = get_val<DWORD>(playerController["m_bPawnHasDefuser"]);
        Offset::PlayerController.HasHelmet = get_val<DWORD>(playerController["m_bPawnHasHelmet"]);

        // WeaponBaseData Offsets
        auto weaponBase = classes["C_BasePlayerWeapon"]["fields"];
        Offset::WeaponBaseData.Clip1 = get_val<DWORD>(weaponBase["m_iClip1"]);
        
        auto weaponVData = classes["CBasePlayerWeaponVData"]["fields"];
        Offset::WeaponBaseData.MaxClip = get_val<DWORD>(weaponVData["m_iMaxClip1"]);
        
        auto csWeaponVData = classes["CCSWeaponBaseVData"]["fields"];
        Offset::WeaponBaseData.CycleTime = get_val<DWORD>(csWeaponVData["m_flCycleTime"]);
        Offset::WeaponBaseData.Penetration = get_val<DWORD>(csWeaponVData["m_flPenetration"]);
        Offset::WeaponBaseData.WeaponType = get_val<DWORD>(csWeaponVData["m_WeaponType"]);
        Offset::WeaponBaseData.Inaccuracy = get_val<DWORD>(csWeaponVData["m_flInaccuracyMove"]);
        Offset::WeaponBaseData.inReload = get_val<DWORD>(csPawn["m_bInReload"]);

        // C4 Offsets
        auto plantedC4 = classes["C_PlantedC4"]["fields"];
        Offset::C4.m_bBeingDefused = get_val<DWORD>(plantedC4["m_bBeingDefused"]);
        Offset::C4.m_flDefuseCountDown = get_val<DWORD>(plantedC4["m_flDefuseCountDown"]);
        Offset::C4.m_nBombSite = get_val<DWORD>(plantedC4["m_nBombSite"]);

        // MoneyServices Offsets
        Offset::InGameMoneyServices.MoneyServices = get_val<DWORD>(playerController["m_pInGameMoneyServices"]);
        auto moneyServicesClass = classes["CCSPlayerController_InGameMoneyServices"]["fields"];
        Offset::InGameMoneyServices.Account = get_val<DWORD>(moneyServicesClass["m_iAccount"]);
        Offset::InGameMoneyServices.CashSpentThisRound = get_val<DWORD>(moneyServicesClass["m_iCashSpentThisRound"]);
        Offset::InGameMoneyServices.TotalCashSpent = get_val<DWORD>(moneyServicesClass["m_iTotalCashSpent"]);

        std::cout << "[Info] Successfully parsed all offsets." << std::endl;

    } catch (const std::exception& e) {
        std::cout << "[ERROR] Exception while parsing offsets: " << e.what() << std::endl;
        return false;
    }

	DWORD64 ClientDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("client.dll"));
	if (ClientDLL == 0)
		return false;

	// Update the LocalPlayerPawn pointer
	DWORD64 TempAddress = 0;
	ProcessMgr.ReadMemory(ClientDLL + Offset::LocalPlayerPawn, TempAddress);
	Offset::Pointer = TempAddress;

	return true;
}