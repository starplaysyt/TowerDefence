#include "Level1.h"

void Level1::InitializeLevelContainments() {
	ClearLevelField();

	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 0; y < 4; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 5; y < tileCountY; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	setTileType(tileCountX - 1, 4, TileType::enemySpawner);

	timeAfterRound = 40.0f;
	roundTimer->setMaxTime(timeAfterRound);

	if (AlphaRegister::moneyCount < 100) {
		AlphaRegister::moneyCount = 100;
		AlphaRegister::LogRegisterChanges("moneyCount", "Level1.cpp", "Money is less than should be, set to 100, current value: " + std::to_string(AlphaRegister::moneyCount));
	}
}

Level1::Level1(SDL_Renderer* renderer, int setTileCountX, int setTileCountY)
	: Level(renderer, setTileCountX, setTileCountY, new Level1Interface(renderer, SDL_RenderGetWindow(renderer))) {
	
	inter = dynamic_cast<Level1Interface*>(UInterface);
	InitializeLevelContainments();
}

void Level1::EventBeforeMainDrawLoop() {

}

void Level1::EventBeforeMainUpdateLoop() {
	if (roundTimer->getCurrentTime() >= 0 && roundTimer->getCurrentTime() <= 0.1) {
		switch (AlphaRegister::currentPlayingWave)
		{
		case 1:
			pretendedUnitCount = 5;
			roundTimer->setMaxTime(10.0f);
			break;
		case 2:
			pretendedUnitCount = 10;
			roundTimer->setMaxTime(10.0f);
			break;
		case 3:
			pretendedUnitCount = 15;
			roundTimer->setMaxTime(10.0f);
			break;
		default:
			break;
		}
		roundTimer->resetToZero();
	}

	

	*inter->moneyCountLabel->Text = "Money: " + std::to_string(AlphaRegister::moneyCount);
}

void Level1::EventAfterMainUpdateLoop() {
	*inter->newWaveButton->Text = roundTimer->getCurrentTime() == roundTimer->getMaxTime() ? "Wave is coming" : "Wave in: " + std::to_string(roundTimer->getCurrentTime());

	if (AlphaRegister::isNewWaveRequested) { //wave requester
		if (roundTimer->getCurrentTime() != roundTimer->getMaxTime()) {
			roundTimer->resetToZero();
			AlphaRegister::isNewWaveRequested = false;
		}
	}

	//wave number setter
	if (roundTimer->getCurrentTime() >= 0 && roundTimer->getCurrentTime() <= 0.1) {
		AlphaRegister::currentPlayingWave++;
		AlphaRegister::LogRegisterChanges("currentPlayingWave", "Level1.cpp", "Wave is coming");
		AlphaRegister::moneyCount += 100;
		AlphaRegister::LogRegisterChanges("moneyCount", "Level1.cpp", "Money for wave got, upped to 100, current value: " + std::to_string(AlphaRegister::moneyCount));
	}

	//wave number updater
	*inter->waveNumberLabel->Text = "Wave " + std::to_string(AlphaRegister::currentPlayingWave);

	if (!AlphaRegister::isPlayerAlive) {
		AlphaRegister::isLevelChangingRequested = true;
		AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "Level1.cpp", "Player killed, back to main menu");
		AlphaRegister::currentPlayingLevel = 0;
		AlphaRegister::LogRegisterChanges("currentPlayingLevel", "Level1.cpp", "Player killed, back to main menu");
	}

}

void Level1::EventCheckupEvents(SDL_Event* e) {
    switch (e->type)
    {
        case SDL_MOUSEBUTTONDOWN:
            switch (e->button.button) 
			{
				case SDL_BUTTON_LEFT:
					if (e->button.type == SDL_MOUSEBUTTONUP) break; //if mouseup, do not do something
					switch (AlphaRegister::currentBuildingMode) {
						case ARegisterEnums::Building:
							//Add the selected turret at the mouse position.
							if (isTileWall(e->button.x / 64, e->button.y / 64))
							{
								if (AlphaRegister::moneyCount >= 30) {
									addTurret(assignedRenderer, Vector2D(e->button.x / 64, e->button.y / 64));
									AlphaRegister::moneyCount -= 40;
									AlphaRegister::LogRegisterChanges("moneyCount", "Level1.cpp", "Built a turret, withdrawed 40, current value: " + std::to_string(AlphaRegister::moneyCount));
								}
								
							}
						break;
					}
				break;

				case SDL_BUTTON_RIGHT:
					if (e->button.type == SDL_MOUSEBUTTONUP) break; //if mouseup, do not do something
					if (AlphaRegister::currentBuildingMode == ARegisterEnums::None) break;
					removeTurretsAtMousePosition(Vector2D(e->button.x / 64, e->button.y / 64));
				break;
            }
        break;

        //case SDL_KEYDOWN:
        //    switch (e.key.keysym.scancode) {
        //        //Quit the game.
        //    case SDL_SCANCODE_ESCAPE:
        //        running = false;
        //        break;

        //        //Set the current gamemode.
        //    case SDL_SCANCODE_1:
        //        placementModeCurrent = PlacementMode::wall;
        //        break;

        //    case SDL_SCANCODE_2:
        //        placementModeCurrent = PlacementMode::turret;
        //        break;

        //        //Show/hide the overlay
        //    case SDL_SCANCODE_H:
        //        overlayVisible = !overlayVisible;
        //        break;
        //    }
        //    break;

        //default:
        //    break;
    }
}
