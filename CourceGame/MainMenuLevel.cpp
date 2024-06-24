#include "MainMenuLevel.h"

void MainMenuLevel::InitializeLevelContainments() {
	ClearLevelField();
	switch (AlphaRegister::menuCurrentPlayingLevel)
	{
	case 1:
		InitFirstLevel();
		break;
	case 2:
		InitSecondLevel();
		break;
	case 3:
		InitThirdLevel();
		break;
	default:
		InitFirstLevel();
		break;
	}

	timeAfterRound = 1.5f;
	roundTimer->setMaxTime(timeAfterRound);
}

MainMenuLevel::MainMenuLevel(SDL_Renderer* renderer, int setTileCountX, int setTileCountY) 
	: Level(renderer, setTileCountX, setTileCountY, new MainMenuInterface(renderer, SDL_RenderGetWindow(renderer))) {

	MainMenuInter = dynamic_cast<MainMenuInterface*>(UInterface);
	InitializeLevelContainments();
}

void MainMenuLevel::EventBeforeMainDrawLoop() {
	//std::cout << roundTimer->getCurrentTime() << std::endl;
}

void MainMenuLevel::EventAfterMainUpdateLoop() {
	if (listUnits.size() > 0) wasUnitsSpawned = true;
	if (roundTimer->getCurrentTime() < timeAfterRound - 0.5f && wasUnitsSpawned) {
		AlphaRegister::menuCurrentPlayingLevel = AlphaRegister::menuCurrentPlayingLevel == 3 ? 1 : AlphaRegister::menuCurrentPlayingLevel + 1;
		wasUnitsSpawned = false;
		InitializeLevelContainments();
	}
}

void MainMenuLevel::InitFirstLevel() {
	std::cout << "FirstLevelInited" << std::endl;
	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	addTurret(assignedRenderer, Vector2D(8, 2));
	addTurret(assignedRenderer, Vector2D(9, 2));

	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 6; y < tileCountY; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	setTileType(tileCountX - 1, 4, TileType::enemySpawner);
}

void MainMenuLevel::InitSecondLevel() {
	std::cout << "SecondLevelInited" << std::endl;
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
}

void MainMenuLevel::InitThirdLevel() {
	std::cout << "ThirdLevelInited" << std::endl;
	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	for (size_t x = 0; x < tileCountX; x++)
	{
		for (size_t y = 6; y < tileCountY; y++)
		{
			setTileType(x, y, TileType::wall);
		}
	}

	setTileType(tileCountX - 1, 5, TileType::enemySpawner);
}