#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "SDL.h"



class TextureLoader
{
public:
	static int loadTexture(SDL_Renderer* renderer, std::string filename);
	static void deallocateTextures();
	
	static SDL_Texture* getTextureFromPool(int id);

private:
	static std::unordered_map<std::string, SDL_Texture*> umapTexturesLoaded;
	static std::vector<SDL_Texture*> texturePool;
};