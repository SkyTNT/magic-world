#pragma once
#include <map>
#include <queue>
#include <vector>
#include <glm/vec3.hpp>
#include <mutex>
#include <condition_variable>
#include "../../utils/VecUtils.h"
#include "../../block/Block.h"

#define CHUNK_SIZE 16

class ObjectGroup;
class BlockObjectGroup;
class World;

class Chunk
{
private:

    class ChunkSection
    {
    public:
        BlockIdAndData mBlocks[CHUNK_SIZE][CHUNK_SIZE];
        ChunkSection();
    };

public:
    glm::ivec3 pos;
    std::map<int ,ChunkSection*>chunkSections;
    std::mutex mMutex;
    BlockObjectGroup*blockObjGroup;

    Chunk(World* _world);
    virtual ~Chunk();

    void setPos(glm::ivec3 _pos);
    void setBlock(glm::ivec3 bpos,int id,int data);
    void setBlock(int x,int y,int z,int id,int data);
    BlockIdAndData getBlock(glm::ivec3 bpos);
    void updateBlock(glm::ivec3 bpos);
    void updateChunk();

    void tick(float dtime);

private:
    World* world;
    bool updateing;
    std::queue<glm::ivec3>*prepareUpdate;

};
