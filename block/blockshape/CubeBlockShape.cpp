#include "CubeBlockShape.h"
#include "../../client/render/RendererContext.h"
#include "../../world/World.h"
#include "../../world/chunk/Chunk.h"
#include "../../client/render/objectgroup/BlockObjectGroup.h"
#include "../../utils/Utils.h"
#include "../../main.h"

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

}

void CubeBlockShape::addToWorld(World *world,glm::ivec3 bpos,glm::vec3 pos,BlockIdAndData idAndData)
{
    Chunk* chunk=world->getChunk(bpos);
    if(chunk==NULL)
    {
        LOG_I("chunk null when adding shape");
        return;
    }
    BlockObjectGroup* objGroup=chunk->blockObjGroup;

    glm::vec3 offset(bpos-chunk->pos);

    Texture *tex=Block::mBlocks[idAndData.id]->getTexture(0);
    if(world->getBlock(bpos+glm::ivec3{0,0,-1}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,
                              0.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 0.0f, 0.0f,
                              1.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 0.0f, 1.0f,tex);
            objGroup->addFace(1.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 0.0f, 1.0f,
                              1.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 1.0f,
                              0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,tex);
        });

    }

    if(world->getBlock(bpos+glm::ivec3{0,0,1}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(0.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,
                              1.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 1.0f, 0.0f,
                              1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 1.0f,tex);
            objGroup->addFace(1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 1.0f,
                              0.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 0.0f, 1.0f,
                              0.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,tex);
        });

    }

    if(world->getBlock(bpos+glm::ivec3{-1,0,0}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(0.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 1.0f,
                              0.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,
                              0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 0.0f, 0.0f,tex);
            objGroup->addFace(0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 0.0f, 0.0f,
                              0.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 1.0f,
                              0.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 1.0f,tex);
        });

    }

    if(world->getBlock(bpos+glm::ivec3{1,0,0}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 0.0f, 1.0f,
                              1.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,
                              1.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,tex);
            objGroup->addFace(1.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,
                              1.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 1.0f, 1.0f,
                              1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 0.0f, 1.0f,tex);
        });

    }

    if(world->getBlock(bpos+glm::ivec3{0,-1,0}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 1.0f,
                              1.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 0.0f,
                              1.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,tex);
            objGroup->addFace(1.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,
                              0.0f+offset.x, 0.0f+offset.y, 1.0f+offset.z, 0.0f, 1.0f,
                              0.0f+offset.x, 0.0f+offset.y, 0.0f+offset.z, 1.0f, 1.0f,tex);
        });

    }

    if(world->getBlock(bpos+glm::ivec3{0,1,0}).id!=idAndData.id)
    {
        commitMainThreadTask([objGroup,offset,tex]
        {
            objGroup->addFace(0.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 0.0f, 1.0f,
                              0.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 0.0f, 0.0f,
                              1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 0.0f,tex);
            objGroup->addFace(1.0f+offset.x, 1.0f+offset.y, 1.0f+offset.z, 1.0f, 0.0f,
                              1.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 1.0f, 1.0f,
                              0.0f+offset.x, 1.0f+offset.y, 0.0f+offset.z, 0.0f, 1.0f,tex);
        });

    }

}

