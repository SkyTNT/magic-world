#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "block/BlockIdAndData.h"

class Player;
class ChunkManager;
class WorldGenerator;
class GameClient;
class ThreadPool;
class Chunk;

class World
{
public:
    Player*mainPlayer;
    ChunkManager*chunkmanager;
    WorldGenerator *worldgenerator;
    ThreadPool*worldThreadPool;

    World(GameClient* _client);
    virtual ~World();

    virtual void init(int _seed);
    virtual void tick(float dtime);

    Chunk* getChunk(glm::vec3 pos);
    Chunk* getChunk(glm::ivec3 pos);
    BlockIdAndData getBlock(glm::ivec3 pos);
    void setBlock(glm::ivec3 pos,BlockIdAndData idanddata);

private:
    GameClient* client;
};
