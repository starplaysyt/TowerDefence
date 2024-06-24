#pragma once
#include <memory>
#include <vector>
#include "SDL.h"
#include "Vector2D.h"
#include "TextureLoader.h"
#include "Timer.h"
class Level;


class Unit
{
public:
	Unit(SDL_Renderer* renderer, Vector2D setPos);
	void update(float dT, Level& level, std::vector<std::shared_ptr<Unit>>& listUnits);
	void draw(SDL_Renderer* renderer, int tileSize);
	bool checkOverlap(Vector2D posOther, float sizeOther);
	bool isAlive();
	Vector2D getPos();
	void removeHealth(int damage);


private:
	Vector2D pos;
	static const float speed;
	static const float size;

	int texture = -1;

	Timer timerJustHurt;

	const int healthMax = 2;
	int healthCurrent = healthMax;
};