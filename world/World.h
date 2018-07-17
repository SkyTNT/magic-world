#pragma once

#include <vector>
#include <glm/vec3.hpp>

#define MAX_CHUNK 16

class Player;
class Chunk;
class WorldGenerator;
class GameClient;
class ThreadPool;
struct BlockIdAndData;

class World
{
public:
    Player*mainPlayer;
    Chunk *mChunks[MAX_CHUNK*MAX_CHUNK];
    WorldGenerator *worldgenerator;
    unsigned int centerChunk;
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
