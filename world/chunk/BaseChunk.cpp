#include "BaseChunk.h"
#include "../../client/render/ObjectGroup.h"
#include <glm/vec3.hpp>
BaseChunk::BaseChunk()
{
objGroup=new ObjectGroup();
objGroup->init();
}

BaseChunk::~BaseChunk()
{
    delete objGroup;
    mBlocks.clear();
}

float vertices[] =
    {
        0, 0, 0,0.0f,  0.0f, -1.0f,
        0,  1,0,0.0f,  0.0f, -1.0f,
        1,  1, 0,0.0f,  0.0f, -1.0f,
        1,  1, 0,0.0f,  0.0f, -1.0f,
        1, 0, 0,0.0f,  0.0f, -1.0f,
        0, 0, 0,0.0f,  0.0f, -1.0f,

        0, 0,  1,0.0f,  0.0f,  1.0f,
        1, 0,  1,0.0f,  0.0f,  1.0f,
        1,  1,  1, 0.0f,  0.0f,  1.0f,
        1,  1,  1, 0.0f,  0.0f,  1.0f,
        0,  1,  1, 0.0f,  0.0f,  1.0f,
        0, 0,  1, 0.0f,  0.0f,  1.0f,

        0,  1,  1,-1.0f,  0.0f,  0.0f,
        0,  1, 0,-1.0f,  0.0f,  0.0f,
        0, 0, 0, -1.0f,  0.0f,  0.0f,
        0, 0, 0, -1.0f,  0.0f,  0.0f,
        0, 0,  1, -1.0f,  0.0f,  0.0f,
        0,  1,  1, -1.0f,  0.0f,  0.0f,

        1,  1,  1, 1.0f,  0.0f,  0.0f,
        1, 0,  1, 1.0f,  0.0f,  0.0f,
        1, 0, 0,1.0f,  0.0f,  0.0f,
        1, 0, 0, 1.0f,  0.0f,  0.0f,
        1,  1, 0, 1.0f,  0.0f,  0.0f,
        1,  1,  1, 1.0f,  0.0f,  0.0f,

        0, 0, 0, 0.0f, -1.0f,  0.0f,
        1, 0, 0, 0.0f, -1.0f,  0.0f,
        1, 0, 1, 0.0f, -1.0f,  0.0f,
        1, 0,  1, 0.0f, -1.0f,  0.0f,
        0, 0,  1, 0.0f, -1.0f,  0.0f,
        0, 0, 0, 0.0f, -1.0f,  0.0f,

        0,  1, 0, 0.0f,  1.0f,  0.0f,
        0,  1,  1, 0.0f,  1.0f,  0.0f,
        1,  1, 1, 0.0f,  1.0f,  0.0f,
        1,  1,  1, 0.0f,  1.0f,  0.0f,
        1,  1, 0, 0.0f,  1.0f,  0.0f,
        0,  1, 0, 0.0f,  1.0f,  0.0f,
};

void BaseChunk::setPos(glm::ivec3 _pos)
{
    pos=_pos;
    objGroup->position=_pos;
}

void BaseChunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    mBlocks[bpos]=BlockIdAndData{id,data};
    ObjectGroup::Buffer buff=objGroup->getBuffer(objGroup->allocateBuffer(36));
    objGroup->writeBuffer(buff,vertices,36);
    objGroup->translate(buff,glm::vec3(bpos-pos));
}
void BaseChunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}
