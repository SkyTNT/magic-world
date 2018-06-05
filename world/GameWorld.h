#pragma once

#include <vector>

#define MAX_CHUNK 16

class Player;
class BaseChunk;
class WorldGenerator;

class GameWorld
{
public:
    Player*mainPlayer;
    BaseChunk *mChunks[MAX_CHUNK*MAX_CHUNK];
    WorldGenerator *worldgenerator;
    unsigned int centerChunk;

    GameWorld();
    virtual ~GameWorld();

    virtual void init(int _seed);
    virtual void tick(float dtime);
};
