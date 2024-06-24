#include "Level.h"

Level::Level(SDL_Renderer* renderer, int setTileCountX, int setTileCountY, Interface::UserInterface *assInter) :
    tileCountX(setTileCountX), tileCountY(setTileCountY),
    targetX(setTileCountX / 2), targetY(setTileCountY / 2) {

    assignedRenderer = renderer;

    spawnTimer = new Timer(timeAfterSpawn);
    roundTimer = new Timer(timeAfterRound);

    UInterface = assInter;
    textureTileWall = TextureLoader::loadTexture(renderer, "Tile Wall.bmp");
    textureTileTarget = TextureLoader::loadTexture(renderer, "Tile Target.bmp");
    textureTileEnemySpawner = TextureLoader::loadTexture(renderer, "Tile Enemy Spawner.bmp");

    size_t listTilesSize = (size_t)tileCountX * tileCountY;
    listTiles.assign(listTilesSize, Tile{});

    //Add an enemy spawner at each corner.

    InitializeLevelContainments();

    calculateFlowField();
}

void Level::draw(SDL_Renderer* renderer, int tileSize) {
    EventBeforeMainDrawLoop(); //placeholder for updating in child-classes

    //Draw the tile's background color.
    for (int y = 0; y < tileCountY; y++) {
        for (int x = 0; x < tileCountX; x++) {
            if ((x + y) % 2 == 0)
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            else
                SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);

            SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //Draw the target tile.
    if (textureTileTarget != -1) {
        SDL_Rect rect = { targetX * tileSize, targetY * tileSize, tileSize, tileSize };
        SDL_RenderCopy(renderer, TextureLoader::getTextureFromPool(textureTileTarget), NULL, &rect);
    }
    
    //Draw the wall tiles.
    for (int y = 0; y < tileCountY; y++) {
        for (int x = 0; x < tileCountX; x++) {
            if (getTileType(x, y) == TileType::enemySpawner) {
                SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
                SDL_RenderCopy(renderer, TextureLoader::getTextureFromPool(textureTileEnemySpawner), NULL, &rect);
            }
            if (isTileWall(x, y)) {
                int w, h;
                SDL_QueryTexture(TextureLoader::getTextureFromPool(textureTileWall), NULL, NULL, &w, &h);
                SDL_Rect rect = {
                    x * tileSize + tileSize / 2 - w / 2,
                    y * tileSize + tileSize / 2 - h / 2,
                    w,
                    h };
                SDL_RenderCopy(renderer, TextureLoader::getTextureFromPool(textureTileWall), NULL, &rect);
            }
        }
    }

    for (auto& unitSelected : listUnits)
        if (unitSelected != nullptr)
            unitSelected->draw(renderer, tileSize);

    //Draw the turrets.
    for (auto& turretSelected : listTurrets)
        turretSelected.draw(renderer, tileSize);

    //Draw the projectiles.
    for (auto& projectileSelected : listProjectiles)
        projectileSelected.draw(renderer, tileSize);

    UInterface->Draw();

    EventAfterMainDrawLoop(); //placeholder for updating in child-classes
}

void Level::drawTile(SDL_Renderer* renderer, int x, int y, int tileSize) {

}

Vector2D Level::getRandomEnemySpawnerLocation() {
    //Create a list of all tiles that are enemy spawners.
    std::vector<int> listSpawnerIndices;
    for (int count = 0; count < listTiles.size(); count++) {
        auto& tileSelected = listTiles[count];
        if (tileSelected.type == TileType::enemySpawner)
            listSpawnerIndices.push_back(count);
    }

    //If one or more spawners are found, pick one at random and output it's center position.
    if (listSpawnerIndices.empty() == false) {
        int index = listSpawnerIndices[rand() % listSpawnerIndices.size()];
        return Vector2D((float)(index % tileCountX) + 0.5f, (float)(index / tileCountX) + 0.5f);
    }

    return Vector2D(0.5f, 0.5f);
}

bool Level::isTileWall(int x, int y) {
    return (getTileType(x, y) == TileType::wall);
}

void Level::setTileWall(int x, int y, bool setWall) {
    if (getTileType(x, y) != TileType::enemySpawner)
        setTileType(x, y, (setWall ? TileType::wall : TileType::empty));
}

Level::TileType Level::getTileType(int x, int y) {
    int index = x + y * tileCountX;
    if (index > -1 && index < listTiles.size() &&
        x > -1 && x < tileCountX &&
        y > -1 && y < tileCountY)
        return listTiles[index].type;

    return TileType::empty;
}

void Level::setTileType(int x, int y, TileType tileType) {
    int index = x + y * tileCountX;
    if (index > -1 && index < listTiles.size() &&
        x > -1 && x < tileCountX &&
        y > -1 && y < tileCountY) {
        listTiles[index].type = tileType;
        calculateFlowField();
    }
}

Vector2D Level::getTargetPos() {
    return Vector2D((float)targetX + 0.5f, (float)targetY + 0.5f);
}

void Level::calculateFlowField() {
    //Ensure the target is in bounds.
    int indexTarget = targetX + targetY * tileCountX;
    if (indexTarget > -1 && indexTarget < listTiles.size() &&
        targetX > -1 && targetX < tileCountX &&
        targetY > -1 && targetY < tileCountY) {

        //Reset the tile flow data.
        for (auto& tileSelected : listTiles) {
            tileSelected.flowDirectionX = 0;
            tileSelected.flowDirectionY = 0;
            tileSelected.flowDistance = flowDistanceMax;
        }

        //Calculate the flow field.
        calculateDistances();
        calculateFlowDirections();
    }
}

void Level::calculateDistances() {
    int indexTarget = targetX + targetY * tileCountX;

    //Create a queue that will contain the indices to be checked.
    std::queue<int> listIndicesToCheck;
    //Set the target tile's flow value to 0 and add it to the queue.
    listTiles[indexTarget].flowDistance = 0;
    listIndicesToCheck.push(indexTarget);

    //The offset of the neighboring tiles to be checked.
    const int listNeighbors[][2] = { { -1, 0}, {1, 0}, {0, -1}, {0, 1} };

    //Loop through the queue and assign distance to each tile.
    while (listIndicesToCheck.empty() == false) {
        int indexCurrent = listIndicesToCheck.front();
        listIndicesToCheck.pop();

        //Check each of the neighbors;
        for (int count = 0; count < 4; count++) {
            int neighborX = listNeighbors[count][0] + indexCurrent % tileCountX;
            int neighborY = listNeighbors[count][1] + indexCurrent / tileCountX;
            int indexNeighbor = neighborX + neighborY * tileCountX;

            //Ensure that the neighbor exists and isn't a wall.
            if (indexNeighbor > -1 && indexNeighbor < listTiles.size() && 
                neighborX > -1 && neighborX < tileCountX &&
                neighborY > -1 && neighborY < tileCountY &&
                listTiles[indexNeighbor].type != TileType::wall) {

                //Check if the tile has been assigned a distance yet or not.
                if (listTiles[indexNeighbor].flowDistance == flowDistanceMax) {
                    //If not the set it's distance and add it to the queue.
                    listTiles[indexNeighbor].flowDistance = listTiles[indexCurrent].flowDistance + 1;
                    listIndicesToCheck.push(indexNeighbor);
                }
            }
        }
    }
}

void Level::calculateFlowDirections() {
    //The offset of the neighboring tiles to be checked.
    const int listNeighbors[][2] = {
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
        {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

    for (int indexCurrent = 0; indexCurrent < listTiles.size(); indexCurrent++) {
        //Ensure that the tile has been assigned a distance value.
        if (listTiles[indexCurrent].flowDistance != flowDistanceMax) {
            //Set the best distance to the current tile's distance.
            unsigned char flowFieldBest = listTiles[indexCurrent].flowDistance;

            //Check each of the neighbors;
            for (int count = 0; count < 8; count++) {
                int offsetX = listNeighbors[count][0];
                int offsetY = listNeighbors[count][1];

                int neighborX = offsetX + indexCurrent % tileCountX;
                int neighborY = offsetY + indexCurrent / tileCountX;
                int indexNeighbor = neighborX + neighborY * tileCountX;

                //Ensure that the neighbor exists.
                if (indexNeighbor > -1 && indexNeighbor < listTiles.size() &&
                    neighborX > -1 && neighborX < tileCountX &&
                    neighborY > -1 && neighborY < tileCountY) {
                    //If the current neighbor's distance is lower than the best then use it.
                    if (listTiles[indexNeighbor].flowDistance < flowFieldBest) {
                        flowFieldBest = listTiles[indexNeighbor].flowDistance;
                        listTiles[indexCurrent].flowDirectionX = offsetX;
                        listTiles[indexCurrent].flowDirectionY = offsetY;
                    }
                }
            }
        }
    }
}

Vector2D Level::getFlowNormal(int x, int y) {
    int index = x + y * tileCountX;
    if (index > -1 && index < listTiles.size() &&
        x > -1 && x < tileCountX &&
        y > -1 && y < tileCountY)
        return Vector2D((float)listTiles[index].flowDirectionX, (float)listTiles[index].flowDirectionY).normalize();

    return Vector2D();
}

void Level::update(SDL_Renderer* renderer, float dT) {
    EventBeforeMainUpdateLoop(); //placeholder for updating in child-classes

    updateUnits(dT);

    //Update the turrets.
    for (auto& turretSelected : listTurrets)
        turretSelected.update(renderer, dT, listUnits, listProjectiles);

    //Update the projectiles.
    updateProjectiles(dT);

    updateSpawnUnitsIfRequired(renderer, dT);

    EventAfterMainUpdateLoop(); //placeholder for updating in child-classes
}

void Level::updateUnits(float dT) {
    //Loop through the list of units and update all of them.
    auto it = listUnits.begin();
    while (it != listUnits.end()) {
        bool increment = true;

        if ((*it) != nullptr) {
            (*it)->update(dT, *this, listUnits);

            //Check if the unit is still alive.  If not then erase it and don't increment the iterator.
            if ((*it)->isAlive() == false) {
                it = listUnits.erase(it);
                increment = false;
            }
        }

        if (increment)
            it++;
    }
}

void Level::updateProjectiles(float dT) {
    //Loop through the list of projectiles and update all of them.
    auto it = listProjectiles.begin();
    while (it != listProjectiles.end()) {
        (*it).update(dT, listUnits);

        //Check if the projectile has collided or not, erase it if needed, and update the iterator.
        if ((*it).getCollisionOccurred())
            it = listProjectiles.erase(it);
        else
            it++;
    }
}

void Level::updateSpawnUnitsIfRequired(SDL_Renderer* renderer, float dT) {
    spawnTimer->countDown(dT);

    //Check if the round needs to start.
    if (listUnits.empty() && spawnUnitCount == 0) {
        roundTimer->countDown(dT);
        if (roundTimer->timeSIsZero()) {
            spawnUnitCount = pretendedUnitCount;
            roundTimer->resetToMax();
        }
    }

    //Add a unit if needed.
    if (spawnUnitCount > 0 && spawnTimer->timeSIsZero()) {
        addUnit(renderer, getRandomEnemySpawnerLocation());

        //Play the spawn unit sound.
        /*if (mix_ChunkSpawnUnit != nullptr)
            Mix_PlayChannel(-1, mix_ChunkSpawnUnit, 0);*/

        spawnUnitCount--;
        spawnTimer->resetToMax();
    }
}

void Level::addUnit(SDL_Renderer* renderer, Vector2D posMouse) {
    listUnits.push_back(std::make_shared<Unit>(renderer, posMouse));
}

void Level::addTurret(SDL_Renderer* renderer, Vector2D posMouse) {
    Vector2D pos((int)posMouse.x + 0.5f, (int)posMouse.y + 0.5f);
    listTurrets.push_back(Turret(renderer, pos));
}

void Level::removeTurretsAtMousePosition(Vector2D posMouse) {
    for (auto it = listTurrets.begin(); it != listTurrets.end();) {
        if ((*it).checkIfOnTile((int)posMouse.x, (int)posMouse.y))
            it = listTurrets.erase(it);
        else
            it++;
    }
}

void Level::DrawInterface() {
    UInterface->Draw();
}

void Level::CheckupEvents(SDL_Event* e) {
    if (!UInterface->CheckupEvents(e)) {
        EventCheckupEvents(e);
    }
}

void Level::EventBeforeMainDrawLoop() {

}

void Level::EventAfterMainDrawLoop() {

}

void Level::EventBeforeMainUpdateLoop() {

}

void Level::EventAfterMainUpdateLoop() {

}

void Level::InitializeLevelContainments() {
    int xMax = tileCountX - 1;
    int yMax = tileCountY - 1;
    setTileType(0, 0, TileType::enemySpawner);
    setTileType(xMax, 0, TileType::enemySpawner);
    setTileType(0, yMax, TileType::enemySpawner);
    setTileType(xMax, yMax, TileType::enemySpawner);
}

void Level::ClearLevelField() {
    listTurrets.clear();

    for (size_t x = 0; x < tileCountX; x++)
    {
        for (size_t y = 0; y < tileCountY; y++)
        {
            setTileType(x, y, TileType::empty);
        }
    }
}

void Level::SetTimers(Timer* spawnTimer, Timer* roundTimer) {
    this->spawnTimer = spawnTimer;
    this->roundTimer = roundTimer;
}

void Level::EventCheckupEvents(SDL_Event* e) {

}

Level::~Level() {
    delete spawnTimer;
    delete roundTimer;
    delete UInterface;
}