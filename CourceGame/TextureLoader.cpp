#include "TextureLoader.h"


std::unordered_map<std::string, SDL_Texture*> TextureLoader::umapTexturesLoaded; //YEEEAAA, BITCH!!!!
std::vector<SDL_Texture*> TextureLoader::texturePool; //YEEEAAA, BITCH!!!!

int TextureLoader::loadTexture(SDL_Renderer* renderer, std::string filename) {
    if (texturePool.size() <= 1) texturePool.push_back(nullptr);
    if (filename != "") {
        auto found = umapTexturesLoaded.find(filename);

        if (found != umapTexturesLoaded.end()) {
            //The texture was already loaded so return it.

            texturePool.push_back(found->second);
            return texturePool.size() - 1;
        }
        else {
            //Setup the relative filepath to the images folder using the input filename.
            std::string filepath = "Data/Images/" + filename;

            //Try to create a surface using the filepath.
            SDL_Surface* surfaceTemp = SDL_LoadBMP(filepath.c_str());
            if (surfaceTemp != nullptr) {

                //The surface was created successfully so attempt to create a texture with it.
                SDL_Texture* textureOutput = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
                //Free the surface because it's no longer needed. 
                SDL_FreeSurface(surfaceTemp);

                if (textureOutput != nullptr) {
                    //Enable transparency for the texture.
                    SDL_SetTextureBlendMode(textureOutput, SDL_BLENDMODE_BLEND);

                    //Add the texture to the map of loaded textures to keep track of it and for clean-up purposes.
                    umapTexturesLoaded[filename] = textureOutput;

                    texturePool.push_back(textureOutput);
                    return texturePool.size() - 1;
                }
            }
        }
    }

    return -1;
}

SDL_Texture* TextureLoader::getTextureFromPool(int id) {
    return texturePool.at(id);
}

void TextureLoader::deallocateTextures() {
    //Destroy all the textures
    while (umapTexturesLoaded.empty() == false) {
        auto it = umapTexturesLoaded.begin();
        if (it->second != nullptr)
            SDL_DestroyTexture(it->second);

        umapTexturesLoaded.erase(it);
    }
}