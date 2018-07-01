#include "CubeBlockShape.h"
#include "../../client/render/RendererContext.h"
#include "../../world/GameWorld.h"
#include "../../world/chunk/BaseChunk.h"
#include "../../client/render/ObjectGroup.h"
#include "../../utils/Utils.h"
CubeBlockShape::CubeBlockShape():BlockShape()
{
    vertices=NULL;
}
CubeBlockShape::~CubeBlockShape()
{
    if(vertices!=NULL)
        delete[] vertices;
}

void CubeBlockShape::init()
{
    vertices =new float[36*8]
    {
        0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,-1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,-1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,-1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,-1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,

    };

}

void CubeBlockShape::addToWorld(GameWorld *world,glm::ivec3 bpos,glm::vec3 pos,BlockIdAndData idAndData,int& buffid)
{
    BaseChunk* chunk=world->getChunk(bpos);
    if(chunk==NULL)
    {
        LOG_I("chunk null when adding shape");
        return;
    }
    ObjectGroup* objGroup=chunk->objGroup;
    if(buffid==0)buffid=objGroup->allocateBuffer(36);

    ObjectGroup::Buffer buff=objGroup->getBuffer(buffid);
    size_t stvert=buff.startVertex;
    if(world->getBlock(bpos+glm::ivec3{0,0,-1}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices,6);
    buff.startVertex+=6;
    if(world->getBlock(bpos+glm::ivec3{0,0,1}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices+6*8,6);
    buff.startVertex+=6;
    if(world->getBlock(bpos+glm::ivec3{-1,0,0}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices+12*8,6);
    buff.startVertex+=6;
    if(world->getBlock(bpos+glm::ivec3{1,0,0}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices+18*8,6);
    buff.startVertex+=6;
    if(world->getBlock(bpos+glm::ivec3{0,-1,0}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices+24*8,6);
    buff.startVertex+=6;
    if(world->getBlock(bpos+glm::ivec3{0,1,0}).id!=idAndData.id)
    objGroup->writeBuffer(buff,vertices+30*8,6);
    buff.startVertex=stvert;
    objGroup->translate(buff,glm::vec3(bpos-chunk->pos));
    objGroup->useTexture(buff,Block::mBlocks[idAndData.id]->getTexture(0));
}

