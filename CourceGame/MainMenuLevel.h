#pragma once
#include "Level.h"
#include "AlphaRegister.h"
#include "MainMenuInterface.h"

class MainMenuLevel : public Level
{
public:
	MainMenuLevel(SDL_Renderer* renderer, int setTileCountX, int setTileCountY);

	//TODO::Add shit to issue every render place, put here sort of cooldown, and reorganize other shit

	void InitializeLevelContainments() override;

	MainMenuInterface * MainMenuInter;

	bool wasUnitsSpawned = false;

	void EventBeforeMainDrawLoop() override;

	void EventAfterMainUpdateLoop() override;

	void InitFirstLevel();

	void InitSecondLevel();

	void InitThirdLevel();

};

