#pragma once
#include <SDL.h>

struct Color {
public:
	Uint8 r, g, b, a;

	Color() {
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Set(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	SDL_Color ToSDL_Color() {
		SDL_Color out;
		out.r = r;
		out.g = g;
		out.b = b;
		out.a = a;
		return out;
	}

	SDL_Color* ToSDL_ColorP() {
		SDL_Color* out = new SDL_Color();
		out->r = r;
		out->g = g;
		out->b = b;
		out->a = a;
		return out;
	}
};