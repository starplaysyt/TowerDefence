#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) :
    placementModeCurrent(PlacementMode::wall)
    {
    //Run the game.
    if (window != nullptr && renderer != nullptr) {
        AlphaRegister::InitializeRegister();
        AlphaRegister::LogRegisterChanges("main", "Game.cpp", "Initialize register data");

        //Load the overlay texture.
        textureOverlay = TextureLoader::loadTexture(renderer, "Overlay.bmp"); //load shitty gameinfo

        //Load the spawn unit sound.
        mix_ChunkSpawnUnit = SoundLoader::loadSound("Spawn Unit.ogg");

        //Store the current times for the clock.
        auto time1 = std::chrono::system_clock::now();
        auto time2 = std::chrono::system_clock::now();

        auto fpsTime1 = std::chrono::system_clock::now();
        auto fpsTime2 = std::chrono::system_clock::now();

        //The amount of time for each frame (60 fps).
        const float dT = 1.0f / 60.0f;

        //Start the game loop and run until it's time to stop.

        AlphaRegister::isLevelChangingRequested = true;
        AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "Game.cpp", "Init menu request");

        int counter = 0;
        while (AlphaRegister::isGameRunning) {
            //Determine how much time has elapsed since the last frame.
            time2 = std::chrono::system_clock::now();
            fpsTime2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();

            std::chrono::duration<float> timeFPSDelta = fpsTime2 - fpsTime1;
            float timeFPSDeltaFloat = timeFPSDelta.count();

            //std::cout << "time fuck";
            //TEC_TODO: create eventary cooldown, this way may take lot of resource. I didnt find any cooldown here. WTF..  
            //TEC_DONE: FPS counter inner and outer, cycle while is unlimited, can cause eventary issues

            //If enough time has passed then do everything required to generate the next frame.
            if (timeDeltaFloat >= dT) {
                //Store the new time for the next frame.
                time1 = time2;
                counter++;

                if (AlphaRegister::isLevelChangingRequested) { //level changing system
                    delete level;
                    switch (AlphaRegister::currentPlayingLevel)
                    {
                        case 0:
                            level = new MainMenuLevel(renderer, windowWidth / tileSize, windowHeight / tileSize);
                        break;
                        case 1:
                            level = new Level1(renderer, windowWidth / tileSize, windowHeight / tileSize);
                        break;
                        case 2:

                        break;
                        default:

                        break;
                    }
                    AlphaRegister::isLevelChangingRequested = false;
                    AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "Game.cpp", "Awnsering on request");
                }

                processEvents(renderer, AlphaRegister::isGameRunning);
                level->update(renderer, dT);
                draw(renderer);
            }
     
            if (timeFPSDeltaFloat >= 1.0f) {
                fpsTime1 = std::chrono::system_clock::now();
                std::cout << counter << std::endl;
                counter = 0;
            }
        }
    }
}

Game::~Game() {
    //Clean up.
    TextureLoader::deallocateTextures();
    SoundLoader::deallocateSounds();
}

void Game::processEvents(SDL_Renderer* renderer, bool& running) {
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;
        level->CheckupEvents(&e);
    }
}

void Game::draw(SDL_Renderer* renderer) {
    //Draw.
    //Set the draw color to white.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //Clear the screen.
    SDL_RenderClear(renderer);

    level->draw(renderer, tileSize);

    SDL_RenderPresent(renderer);
}