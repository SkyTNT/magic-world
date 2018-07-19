#include "Chunk.h"
#include "../World.h"
#include "../../block/blockshape/BlockShape.h"
#include "../../client/render/objectgroup/BlockObjectGroup.h"
#include <string.h>
#include <glm/vec3.hpp>
#include "../../utils/Utils.h"
#include "../../thread/ThreadPool.h"

Chunk::ChunkSection::ChunkSection()
{
    memset(mBlocks,0,sizeof(mBlocks));
}

Chunk::Chunk(World* _world)
{
    world=_world;
    blockObjGroup=new BlockObjectGroup();
    blockObjGroup->init();
    prepareUpdate=new std::queue<glm::ivec3>();
}
Chunk::~Chunk()
{
    delete blockObjGroup;
    for(auto it=chunkSections.begin(); it!=chunkSections.end(); it++)
    {
        if(it->second!=NULL)
            delete it->second;
    }
    chunkSections.clear();
    delete prepareUpdate;
}

void Chunk::setPos(glm::ivec3 _pos)
{
    pos=_pos;
    blockObjGroup->position=_pos;
}

void Chunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    std::lock_guard<std::mutex> lock(mMutex);
    glm::ivec3 dpos=bpos-pos;
    BlockIdAndData idanddata= {id,data};
    ChunkSection *cs;
    auto it=chunkSections.find(dpos.y);
    if(it==chunkSections.end())
    {
        cs=new ChunkSection();
        cs->mBlocks[dpos.x][dpos.z]=idanddata;
        chunkSections[dpos.y]=cs;
        updateBlock(bpos);
        return;
    }
    cs=it->second;
    cs->mBlocks[dpos.x][dpos.z]=idanddata;
    updateBlock(bpos);
}

void Chunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}

BlockIdAndData Chunk::getBlock(glm::ivec3 bpos)
{
    glm::ivec3 dpos=bpos-pos;
    auto it=chunkSections.find(dpos.y);
    if(it==chunkSections.end())
    {
        return BlockIdAndData{0,0};
    }
    return it->second->mBlocks[dpos.x][dpos.z];

}

void Chunk::updateBlock(glm::ivec3 bpos)
{
    prepareUpdate->push(bpos);
}

void Chunk::updateChunk()
{
    std::lock_guard<std::mutex> lock(mMutex);
    if(!prepareUpdate->empty())
    {
        while(!prepareUpdate->empty())
        {

            glm::ivec3 ubpos=prepareUpdate->front();
            prepareUpdate->pop();
            BlockIdAndData idanddata=getBlock(ubpos);
            if(idanddata.id==0)
                continue;
            Block::mBlocks[idanddata.id]->getShape()->addToWorld(world,ubpos,glm::vec3(ubpos),idanddata);
        }
        delete prepareUpdate;
        prepareUpdate=new std::queue<glm::ivec3>();
    }
}

void Chunk::tick(float dtime)
{

}
