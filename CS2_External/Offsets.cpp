#include "Offsets.h"

DWORD64 SearchOffsets(std::string Signature, DWORD64 ModuleAddress)
{
	std::vector<DWORD64> TempAddressList;
	DWORD64 Address = 0;
	DWORD Offsets = 0;

	TempAddressList = ProcessMgr.SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);

	if (TempAddressList.size() <= 0)
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD>(TempAddressList.at(0) + 3, Offsets))
		return 0;

	Address = TempAddressList.at(0) + Offsets + 7;
	return Address;
}

bool Offset::UpdateOffsets()
{
	DWORD64 ClientDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("client.dll"));
	if (ClientDLL == 0)
		return false;

	DWORD64 ServerDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("server.dll"));
	if (ServerDLL == 0)
		return false;

	DWORD64 InputDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("inputsystem.dll"));
	if (InputDLL == 0)
		return false;

	// Hardcoded offsets from the provided offsets.yaml (Match 16, 2026)
	Offset::EntityList = 0x24AE268;
	Offset::LocalPlayerController = 0x22F3178;
	Offset::Matrix = 0x230EF20;
	Offset::GlobalVars = 0x205D5C0;
	Offset::ViewAngle = 0x2319648;
	Offset::LocalPlayerPawn = 0x2068B60;
	Offset::ForceJump = 0x2061E00;
	Offset::PlantedC4 = 0x2316740;
	Offset::Sensitivity = 0x230A7F8;
	Offset::InputSystem = 0x45AD0;

	// For CS2, viewangles are usually stored as a pointer
	DWORD64 ViewAnglePtr = 0;
	if (ProcessMgr.ReadMemory<DWORD64>(ClientDLL + Offset::ViewAngle, ViewAnglePtr))
	{
		// Offset from the pointer is usually 0
		Offset::ViewAngle = ViewAnglePtr - ClientDLL;
	}

	// Update the LocalPlayerPawn pointer
	DWORD64 TempAddress = 0;
	ProcessMgr.ReadMemory(ClientDLL + Offset::LocalPlayerPawn, TempAddress);
	Offset::Pointer = TempAddress;

	return true;
}