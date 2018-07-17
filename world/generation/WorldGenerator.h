#pragma once

class World;
class Chunk;
class NoiseGenerator;

class WorldGenerator
{
public:
    int seed;
    World* mWorld;
    NoiseGenerator*heightMapGenerator;
    WorldGenerator(int _seed,World* _mWorld);
    virtual ~WorldGenerator();

    virtual void genChunk(Chunk*mchunk);

};
