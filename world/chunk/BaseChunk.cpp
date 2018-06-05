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

void BaseChunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    mBlocks[pos]=BlockIdAndData{id,data};
    objGroup->translate(glm::vec3(bpos-pos));
    objGroup->addVertexBuffer(vertices,36);
}
void BaseChunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}
