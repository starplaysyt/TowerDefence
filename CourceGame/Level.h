#pragma once
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "SDL.h"
#include "Vector2D.h"
#include "TextureLoader.h"
#include "Turret.h"
#include "Projectile.h"
#include "Timer.h"
#include "UserInterface.h"

class Level
{
protected:
	enum class TileType : char {
		empty,
		wall,
		enemySpawner
	};

	static const unsigned char flowDistanceMax = 255;

	struct Tile {
		TileType type = TileType::empty;
		int flowDirectionX = 0;
		int flowDirectionY = 0;
		unsigned char flowDistance = flowDistanceMax;
	};

public:
	Level(SDL_Renderer* renderer, int setTileCountX, int setTileCountY, Interface::UserInterface* assInter);
	void draw(SDL_Renderer* renderer, int tileSize);

	void CheckupEvents(SDL_Event *e);

	virtual void InitializeLevelContainments();

	void ClearLevelField();

	Vector2D getRandomEnemySpawnerLocation();
	bool isTileWall(int x, int y);
	void setTileWall(int x, int y, bool setWall);
	Vector2D getTargetPos();
	Vector2D getFlowNormal(int x, int y);

	void SetTimers(Timer* spawnTimer, Timer* roundTimer);

	void update(SDL_Renderer* renderer, float dT);
	void updateUnits(float dT);
	void updateProjectiles(float dT);
	void updateSpawnUnitsIfRequired(SDL_Renderer* renderer, float dT);
	void addUnit(SDL_Renderer* renderer, Vector2D posMouse);
	void addTurret(SDL_Renderer* renderer, Vector2D posMouse);
	void removeTurretsAtMousePosition(Vector2D posMouse);

protected:
	TileType getTileType(int x, int y);
	void setTileType(int x, int y, TileType tileType);
	void drawTile(SDL_Renderer* renderer, int x, int y, int tileSize);
	void calculateFlowField();
	void calculateDistances();
	void calculateFlowDirections();
	void DrawInterface();

	virtual void EventBeforeMainDrawLoop();
	virtual void EventAfterMainDrawLoop();
	virtual void EventBeforeMainUpdateLoop();
	virtual void EventAfterMainUpdateLoop();
	virtual void EventCheckupEvents(SDL_Event *e);

public:
	SDL_Renderer* assignedRenderer;

	std::vector<std::shared_ptr<Unit>> listUnits;
	std::vector<Turret> listTurrets;
	std::vector<Projectile> listProjectiles;

	Timer* spawnTimer;
	Timer* roundTimer;
	int spawnUnitCount = 0;
	int pretendedUnitCount = 15;
	float timeAfterRound = 5.0f;
	float timeAfterSpawn = 0.25f;

	Interface::UserInterface* UInterface;

	~Level();

protected:
	std::vector<Tile> listTiles;
	const int tileCountX, tileCountY;

	const int targetX = 0, targetY = 0;

	int textureTileWall = -1,
		textureTileTarget = -1,
		textureTileEnemySpawner = -1,
		textureTileEmpty = -1;


};