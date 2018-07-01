#pragma once

#include <vector>
#include <glm/vec3.hpp>

#define MAX_CHUNK 16

class Player;
class BaseChunk;
class WorldGenerator;
class GameClient;
struct BlockIdAndData;

class GameWorld
{
public:
    Player*mainPlayer;
    BaseChunk *mChunks[MAX_CHUNK*MAX_CHUNK];
    WorldGenerator *worldgenerator;
    unsigned int centerChunk;

    GameWorld(GameClient* _client);
    virtual ~GameWorld();

    virtual void init(int _seed);
    virtual void tick(float dtime);

    BaseChunk* getChunk(glm::vec3 pos);
    BaseChunk* getChunk(glm::ivec3 pos);
    BlockIdAndData getBlock(glm::ivec3 pos);
private:
    GameClient* client;
};
