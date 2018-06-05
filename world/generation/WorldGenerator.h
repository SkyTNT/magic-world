#pragma once

class GameWorld;
class BaseChunk;
class NoiseGenerator;

class WorldGenerator
{
public:
    int seed;
    GameWorld* mWorld;
    NoiseGenerator*heightMapGenerator;
    WorldGenerator(int _seed,GameWorld* _mWorld);
    virtual ~WorldGenerator();

    virtual void genChunk(BaseChunk*mchunk);

};
