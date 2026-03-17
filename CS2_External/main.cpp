#define _CRT_SECURE_NO_WARNINGS
#include "Cheats.h"
#include "Offsets.h"
#include "Resources/Language.h"
#include "Utils/Initial/Init.h"
#include "Utils/Initial/KeyAuth.hpp"
#include <KnownFolders.h>
#include <ShlObj.h>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <stdio.h>

using namespace std;
/*
Contributors:
        Shinyaluvs,
        Nx0Ri,
        Skarbor,
        PedroGoncalves,
        KeysIsCool,
        Kenny,
        Cr1ppl3,
        Tairitsu,
        sh1pi,
        toepas,
        djsacred,
        tokinaa,
        faster_bbc,
        vsantos1,
        5mmod,
        gScream,
        Hazetick,
        styx,
        user1232,
        TaKaStuKi.sen
*/

namespace fs = filesystem;

void Exit() {
  system("pause");
  exit(0);
}

void Cheat() {
  if (Init::Verify::CheckWindowVersion())
    Lang::GetCountry(MenuConfig::Country);
  HANDLE hConsole =
      GetStdHandle(STD_OUTPUT_HANDLE); // Gets a standard output device handle
  SetConsoleTextAttribute(hConsole,
                          FOREGROUND_BLUE |
                              FOREGROUND_GREEN); // Set the text color to green
  cout << R"(
 /$$                                     /$$ /$$   /$$           /$$                 /$$                
| $$                                    | $$| $$  | $$          | $$                | $$                
| $$        /$$$$$$  /$$    /$$ /$$$$$$ | $$| $$  | $$  /$$$$$$ | $$        /$$$$$$ | $$$$$$$   /$$$$$$$
| $$       /$$__  $$|  $$  /$$//$$__  $$| $$| $$  | $$ /$$__  $$| $$       |____  $$| $$__  $$ /$$_____/
| $$      | $$$$$$$$ \  $$/$$/| $$$$$$$$| $$| $$  | $$| $$  \ $$| $$        /$$$$$$$| $$  \ $$|  $$$$$$ 
| $$      | $$_____/  \  $$$/ | $$_____/| $$| $$  | $$| $$  | $$| $$       /$$__  $$| $$  | $$ \____  $$
| $$$$$$$$|  $$$$$$$   \  $/  |  $$$$$$$| $$|  $$$$$$/| $$$$$$$/| $$$$$$$$|  $$$$$$$| $$$$$$$/ /$$$$$$$/
|________/ \_______/    \_/    \_______/|__/ \______/ | $$____/ |________/ \_______/|_______/ |_______/ 
                                                      | $$                                              
                                                      | $$                                              
                                                      |__/                                              
	)"
       << endl;
  SetConsoleTextAttribute(hConsole,
                          FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

  auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

  char documentsPath[MAX_PATH];
  if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath) != S_OK) {
    cerr << "[Info] Error: Failed to get the Documents folder path." << endl;
    Exit();
  }
  MenuConfig::path = documentsPath;
  MenuConfig::path += "\\LevelUpLabs";

  switch (ProcessStatus) {
  case 1:
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[ERROR] Please launch the game first!" << endl;
    Exit();
  case 2:
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[ERROR] Failed to hook process, please run the cheat as "
            "Administrator (Right click LevelUpLabs > Run as Adminstrator)."
         << endl;
    Exit();
  case 3:
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[ERROR] Failed to get module address." << endl;
    Exit();
  default:
    break;
  }

  if (!Offset::UpdateOffsets()) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[ERROR] Failed to update offsets." << endl;
    Exit();
  }

  if (!gGame.InitAddress()) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[ERROR] Failed to call InitAddress()." << endl;
    Exit();
  }

  cout << "[Game] Process ID: " << ProcessMgr.ProcessID << endl;
  cout << "[Game] Client Address: " << gGame.GetClientDLLAddress() << endl;

  if (fs::exists(MenuConfig::path)) {
    cout << "[Info] Config folder connected: " << MenuConfig::path << endl;
  } else {
    if (fs::create_directory(MenuConfig::path)) {
      cout << "[Info] Config folder created: " << MenuConfig::path << endl;
    } else {
      cerr << "[Info] Error: Failed to create the config directory." << endl;
      Exit();
    }
  }

  cout << endl;
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
  cout << "Cheat running successfully!" << endl;
  cout << "Press [INS] to show or hide Menu." << endl;
  cout << "Have fun..." << endl << endl;
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
  cout << "=======[ Offset List ]=======" << endl;
  cout << setw(23) << left << "EntityList:" << setiosflags(ios::uppercase)
       << hex << Offset::EntityList << endl;
  cout << setw(23) << left << "Matrix:" << setiosflags(ios::uppercase) << hex
       << Offset::Matrix << endl;
  cout << setw(23) << left
       << "LocalPlayerController:" << setiosflags(ios::uppercase) << hex
       << Offset::LocalPlayerController << endl;
  cout << setw(23) << left << "ViewAngles:" << setiosflags(ios::uppercase)
       << hex << Offset::ViewAngle << endl;
  cout << setw(23) << left << "LocalPlayerPawn:" << setiosflags(ios::uppercase)
       << hex << Offset::LocalPlayerPawn << endl;
  cout << setw(23) << left << "PlantedC4:" << setiosflags(ios::uppercase) << hex
       << Offset::PlantedC4 << endl;
  cout << setw(23) << left << "ForceJump:" << setiosflags(ios::uppercase) << hex
       << Offset::ForceJump << endl;
  cout << setw(23) << left << "Sensitivity:" << setiosflags(ios::uppercase)
       << hex << Offset::Sensitivity << endl;
  cout << endl;
  SetConsoleTextAttribute(hConsole,
                          FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

  try {
    Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
  } catch (OSImGui::OSException &e) {
    try {
      // Perfect World version
      Gui.AttachAnotherWindow("反恐精英：全球攻势", "SDL_app", Cheats::Run);
    } catch (OSImGui::OSException &e) {
      cout << e.what() << endl;
    }
  }
}

int main() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
  cout << R"(
 /$$                                     /$$ /$$   /$$           /$$                 /$$                
| $$                                    | $$| $$  | $$          | $$                | $$                
| $$        /$$$$$$  /$$    /$$ /$$$$$$ | $$| $$  | $$  /$$$$$$ | $$        /$$$$$$ | $$$$$$$   /$$$$$$$
| $$       /$$__  $$|  $$  /$$//$$__  $$| $$| $$  | $$ /$$__  $$| $$       |____  $$| $$__  $$ /$$_____/
| $$      | $$$$$$$$ \  $$/$$/| $$$$$$$$| $$| $$  | $$| $$  \ $$| $$        /$$$$$$$| $$  \ $$|  $$$$$$ 
| $$      | $$_____/  \  $$$/ | $$_____/| $$| $$  | $$| $$  | $$| $$       /$$__  $$| $$  | $$ \____  $$
| $$$$$$$$|  $$$$$$$   \  $/  |  $$$$$$$| $$|  $$$$$$/| $$$$$$$/| $$$$$$$$|  $$$$$$$| $$$$$$$/ /$$$$$$$/
|________/ \_______/    \_/    \_______/|__/ \______/ | $$____/ |________/ \_______/|_______/ |_______/ 
                                                      | $$                                              
                                                      | $$                                              
                                                      |__/                                              
	)"
       << endl;

  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

  cout << "[Auth] Connecting to license server..." << endl;

  string key;
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
  cout << "Enter your license key: ";
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
  cin >> key;
  cout << endl;

  SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
  cout << "[Auth] Validating key, please wait..." << endl;

  if (!KeyAuth::initialize(key)) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[Auth] Authentication failed. Exiting." << endl;
    Exit();
  }

  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
  cout << "[Auth] License verified successfully! Loading..." << endl;
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
  system("cls");

  Cheat();
  return 0;
}
