#pragma once
#include <map>
#include <vector>
#include <glm/vec3.hpp>
#include "../../utils/VecUtils.h"
#include "../../block/Block.h"

#define CHUNK_SIZE 16

class ObjectGroup;

class BaseChunk
{
public:
    glm::ivec3 pos;
    std::map<glm::ivec3,BlockIdAndData,ivec3cmp>mBlocks;
    ObjectGroup*objGroup;
    BaseChunk();
    virtual ~BaseChunk();
    void setPos(glm::ivec3 _pos);
    void setBlock(glm::ivec3 bpos,int id,int data);
    void setBlock(int x,int y,int z,int id,int data);
};
