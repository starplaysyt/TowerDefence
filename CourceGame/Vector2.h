#pragma once

class Vector2
{
public:
	int x, y;

	void Set(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Vector2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	
	Vector2() {
		x = 0;
		y = 0;
	}
};