#pragma once
#include <iostream>

namespace ARegisterEnums {
	enum ARegisterCurrentGameMode {
		Menu, Game, SubMenu
	};

	enum ARegisterCurrentBuildingMode {
		None, Building
	};
}

class AlphaRegister {
public:
	static bool isGameRunning;
	static ARegisterEnums::ARegisterCurrentGameMode currentGameMode;
	static int currentPlayingLevel;
	static bool isLevelChangingRequested;
	static int moneyCount;
	static int menuCurrentPlayingLevel;
	static ARegisterEnums::ARegisterCurrentBuildingMode currentBuildingMode;
	static bool isNewWaveRequested;
	static bool isPlayerAlive;
	static int currentPlayingWave;

	static void InitializeRegister() {
		isGameRunning = true;
		currentGameMode = ARegisterEnums::Menu;
		currentPlayingLevel = 0;
		moneyCount = 0;
		menuCurrentPlayingLevel = 1;
		currentBuildingMode = ARegisterEnums::None;
		isNewWaveRequested = false;
		isLevelChangingRequested = false;
		isPlayerAlive = true;
		currentPlayingWave = 0;
	}

	static void LogRegisterChanges(std::string value, std::string sender, std::string info) {
		std::cout << "Alpha register >> Register value " << value << " changed by " << sender << " with info: " << info << std::endl;
	}
};


