#pragma once
#include "Level.h"
#include "AlphaRegister.h"
#include "Level1Interface.h"

class Level1 : public Level
{
public:
	Level1(SDL_Renderer* renderer, int setTileCountX, int setTileCountY);

	void InitializeLevelContainments() override;

	Level1Interface *inter;

	int currentWave = 0;

	void EventBeforeMainDrawLoop() override;

	void EventAfterMainUpdateLoop() override;

	void EventBeforeMainUpdateLoop() override;

	void EventCheckupEvents(SDL_Event *e) override;
};

