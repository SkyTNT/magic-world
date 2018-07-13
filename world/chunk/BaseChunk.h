#pragma once
#include <map>
#include <queue>
#include <vector>
#include <glm/vec3.hpp>
#include "../../utils/VecUtils.h"
#include "../../block/Block.h"

#define CHUNK_SIZE 16

class ObjectGroup;
class BlockObjectGroup;
class GameWorld;

class BaseChunk
{
private:

    struct ChunkSection
    {
        int height;
        BlockIdAndData mBlocks[CHUNK_SIZE][CHUNK_SIZE];
    };

public:
    glm::ivec3 pos;
    std::map<glm::ivec3,BlockIdAndData,ivec3cmp>mBlocks;
    BlockObjectGroup*blockObjGroup;

    BaseChunk(GameWorld* _world);
    virtual ~BaseChunk();

    void setPos(glm::ivec3 _pos);
    void setBlock(glm::ivec3 bpos,int id,int data);
    void setBlock(int x,int y,int z,int id,int data);
    BlockIdAndData getBlock(glm::ivec3 bpos);
    void updateBlock(glm::ivec3 bpos);

    void tick(float dtime);

private:

    GameWorld* world;
    std::queue<glm::ivec3>*prepareUpdate;

};
