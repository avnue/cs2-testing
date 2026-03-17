#include "Offsets.h"
#include <string>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include <iostream>

bool Offset::UpdateOffsets()
{
    try {
        std::string yamlPath = "offsets.yaml";
        
        // Try current directory, then one level up
        std::ifstream f(yamlPath);
        if (!f.good()) {
            yamlPath = "../offsets.yaml";
            f.open(yamlPath);
        }
        
        if (!f.good()) {
            std::cout << "[ERROR] Could not find offsets.yaml in current or parent directory." << std::endl;
            return false;
        }
        f.close();

        YAML::Node config = YAML::LoadFile(yamlPath);
        auto client = config["client_dll"];
        auto engine = config["engine2_dll"];
        auto input = config["inputsystem_dll"];
        auto classes = client["classes"];

        // Global Offsets
        Offset::EntityList = client["dwEntityList"].as<DWORD>();
        Offset::LocalPlayerController = client["dwLocalPlayerController"].as<DWORD>();
        Offset::LocalPlayerPawn = client["dwLocalPlayerPawn"].as<DWORD>();
        Offset::GlobalVars = client["dwGlobalVars"].as<DWORD>();
        Offset::ViewAngle = client["dwViewAngles"].as<DWORD>();
        Offset::Matrix = client["dwViewMatrix"].as<DWORD>();
        Offset::PlantedC4 = client["dwPlantedC4"].as<DWORD>();
        Offset::Sensitivity = client["dwSensitivity"].as<DWORD>();
        Offset::InputSystem = input["dwInputSystem"].as<DWORD>();
        Offset::ForceJump = client["jump"].as<DWORD>();
        Offset::ForceCrouch = client["duck"].as<DWORD>();
        Offset::ForceForward = client["forward"].as<DWORD>();
        Offset::ForceLeft = client["left"].as<DWORD>();
        Offset::ForceRight = client["right"].as<DWORD>();

        // Entity Offsets (mapped from YAML classes)
        auto baseEntity = classes["C_BaseEntity"]["fields"];
        auto playerController = classes["CCSPlayerController"]["fields"];
        
        Offset::Entity.Health = playerController["m_iPawnHealth"].as<DWORD>();
        Offset::Entity.TeamID = baseEntity["m_iTeamNum"].as<DWORD>();
        Offset::Entity.IsAlive = playerController["m_bPawnIsAlive"].as<DWORD>();
        Offset::Entity.PlayerPawn = playerController["m_hPawn"].as<DWORD>();
        Offset::Entity.iszPlayerName = playerController["m_iszPlayerName"].as<DWORD>();

        // Pawn Offsets
        auto basePawn = classes["C_BasePlayerPawn"]["fields"];
        auto csPawn = classes["C_CSPlayerPawn"]["fields"];
        
        Offset::Pawn.MovementServices = basePawn["m_pMovementServices"].as<DWORD>();
        Offset::Pawn.WeaponServices = basePawn["m_pWeaponServices"].as<DWORD>();
        Offset::Pawn.BulletServices = csPawn["m_pBulletServices"].as<DWORD>();
        Offset::Pawn.CameraServices = basePawn["m_pCameraServices"].as<DWORD>();
        Offset::Pawn.pClippingWeapon = csPawn["m_pClippingWeapon"].as<DWORD>();
        
        Offset::Pawn.Pos = basePawn["m_vOldOrigin"].as<DWORD>();
        Offset::Pawn.MaxHealth = baseEntity["m_iMaxHealth"].as<DWORD>();
        Offset::Pawn.CurrentHealth = baseEntity["m_iHealth"].as<DWORD>();
        Offset::Pawn.GameSceneNode = baseEntity["m_pGameSceneNode"].as<DWORD>();
        Offset::Pawn.angEyeAngles = csPawn["m_angEyeAngles"].as<DWORD>();
        Offset::Pawn.vecLastClipCameraPos = csPawn["m_vecLastClipCameraPos"].as<DWORD>();
        Offset::Pawn.iShotsFired = csPawn["m_iShotsFired"].as<DWORD>();
        Offset::Pawn.flFlashMaxAlpha = csPawn["m_flFlashMaxAlpha"].as<DWORD>();
        Offset::Pawn.flFlashDuration = csPawn["m_flFlashDuration"].as<DWORD>();
        Offset::Pawn.aimPunchAngle = csPawn["m_aimPunchAngle"].as<DWORD>();
        Offset::Pawn.aimPunchCache = csPawn["m_aimPunchCache"].as<DWORD>();
        Offset::Pawn.iIDEntIndex = csPawn["m_iIDEntIndex"].as<DWORD>();
        Offset::Pawn.iTeamNum = baseEntity["m_iTeamNum"].as<DWORD>();
        Offset::Pawn.fFlags = baseEntity["m_fFlags"].as<DWORD>();

        auto camServices = classes["CPlayer_CameraServices"]["fields"];
        Offset::Pawn.iFovStart = camServices["m_iFOVStart"].as<DWORD>();

        auto spottedState = classes["EntitySpottedState_t"]["fields"];
        Offset::Pawn.bSpottedByMask = csPawn["m_entitySpottedState"].as<DWORD>() + spottedState["m_bSpottedByMask"].as<DWORD>();

        // PlayerController Offsets
        Offset::PlayerController.m_hPawn = playerController["m_hPawn"].as<DWORD>();
        Offset::PlayerController.m_pObserverServices = basePawn["m_pObserverServices"].as<DWORD>();
        Offset::PlayerController.m_hObserverTarget = classes["CPlayer_ObserverServices"]["fields"]["m_hObserverTarget"].as<DWORD>();
        Offset::PlayerController.m_hController = basePawn["m_hController"].as<DWORD>();
        Offset::PlayerController.PawnArmor = playerController["m_iPawnArmor"].as<DWORD>();
        Offset::PlayerController.HasDefuser = playerController["m_bPawnHasDefuser"].as<DWORD>();
        Offset::PlayerController.HasHelmet = playerController["m_bPawnHasHelmet"].as<DWORD>();

        // WeaponBaseData Offsets
        auto weaponBase = classes["C_BasePlayerWeapon"]["fields"];
        Offset::WeaponBaseData.Clip1 = weaponBase["m_iClip1"].as<DWORD>();
        
        auto weaponVData = classes["CBasePlayerWeaponVData"]["fields"];
        Offset::WeaponBaseData.MaxClip = weaponVData["m_iMaxClip1"].as<DWORD>();
        
        auto csWeaponVData = classes["CCSWeaponBaseVData"]["fields"];
        Offset::WeaponBaseData.CycleTime = csWeaponVData["m_flCycleTime"].as<DWORD>();
        Offset::WeaponBaseData.Penetration = csWeaponVData["m_flPenetration"].as<DWORD>();
        Offset::WeaponBaseData.WeaponType = csWeaponVData["m_WeaponType"].as<DWORD>();
        Offset::WeaponBaseData.Inaccuracy = csWeaponVData["m_flInaccuracyMove"].as<DWORD>();
        Offset::WeaponBaseData.inReload = csPawn["m_bInReload"].as<DWORD>();

        // C4 Offsets
        auto plantedC4 = classes["C_PlantedC4"]["fields"];
        Offset::C4.m_bBeingDefused = plantedC4["m_bBeingDefused"].as<DWORD>();
        Offset::C4.m_flDefuseCountDown = plantedC4["m_flC4Blow"].as<DWORD>(); // Wait, m_flC4Blow is for time remaining?
        Offset::C4.m_nBombSite = plantedC4["m_nBombSite"].as<DWORD>();

        // MoneyServices Offsets
        Offset::InGameMoneyServices.MoneyServices = playerController["m_pInGameMoneyServices"].as<DWORD>();
        auto moneyServicesClass = classes["CCSPlayerController_InGameMoneyServices"]["fields"];
        Offset::InGameMoneyServices.Account = moneyServicesClass["m_iAccount"].as<DWORD>();
        Offset::InGameMoneyServices.CashSpentThisRound = moneyServicesClass["m_iCashSpentThisRound"].as<DWORD>();
        Offset::InGameMoneyServices.TotalCashSpent = moneyServicesClass["m_iTotalCashSpent"].as<DWORD>();

        std::cout << "[Info] Successfully loaded ALL offsets from " << yamlPath << std::endl;

    } catch (const std::exception& e) {
        std::cout << "[ERROR] Exception while parsing offsets.yaml: " << e.what() << std::endl;
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