#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include "SDL.h"
#include "Unit.h"
#include "Level.h"
#include "MainMenuInterface.h"
#include "UserInterface.h"
#include "AlphaRegister.h"
#include "MainMenuLevel.h"
#include "Level1.h"

class Game
{
private:
	enum class PlacementMode {
		wall,
		turret
	} placementModeCurrent;

public:
	Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);
	~Game();
	void draw(SDL_Renderer* renderer);

private:
	void processEvents(SDL_Renderer* renderer, bool& running);

	int mouseDownStatus = 0;

	const int tileSize = 64;
	Level* level;

	int textureOverlay = -1;
	bool overlayVisible = true;

	int spawnUnitCount = 0;

	Mix_Chunk* mix_ChunkSpawnUnit = nullptr;
	
};