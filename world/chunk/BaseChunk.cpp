#include "BaseChunk.h"
#include "../GameWorld.h"
#include "../../block/blockshape/BlockShape.h"
#include "../../client/render/objectgroup/BlockObjectGroup.h"
#include <string.h>
#include <glm/vec3.hpp>
#include "../../utils/Utils.h"
#include "../../thread/ThreadPool.h"

BaseChunk::ChunkSection::ChunkSection()
{
    memset(mBlocks,0,sizeof(mBlocks));
}

BaseChunk::BaseChunk(GameWorld* _world)
{
    world=_world;
    blockObjGroup=new BlockObjectGroup();
    blockObjGroup->init();
    prepareUpdate=new std::queue<glm::ivec3>();
    updateing=false;
}
BaseChunk::~BaseChunk()
{
    //std::unique_lock<std::mutex> lock(mMutex);
    //cond.wait(lock,[this]{return !updateing;});
    delete blockObjGroup;
    for(auto it=chunkSections.begin(); it!=chunkSections.end(); it++)
    {
        if(it->second!=NULL)
            delete it->second;
    }
    chunkSections.clear();
    delete prepareUpdate;
}

void BaseChunk::setPos(glm::ivec3 _pos)
{
    pos=_pos;
    blockObjGroup->position=_pos;
}

void BaseChunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    glm::ivec3 dpos=bpos-pos;
    BlockIdAndData idanddata= {id,data};

    for(auto it=chunkSections.begin(); it!=chunkSections.end(); it++)
    {
        ChunkSection *cs=it->second;
        if(cs==NULL)
            continue;
        if(it->first==dpos.y)
        {
            cs->mBlocks[dpos.x][dpos.z]=idanddata;
            updateBlock(bpos);
            return;
        }
    }
    ChunkSection *cs=new ChunkSection();
    cs->mBlocks[dpos.x][dpos.z]=idanddata;
    chunkSections[dpos.y]=cs;

    updateBlock(bpos);

}

void BaseChunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}

BlockIdAndData BaseChunk::getBlock(glm::ivec3 bpos)
{
    glm::ivec3 dpos=bpos-pos;
    for(auto it=chunkSections.begin(); it!=chunkSections.end(); it++)
    {
        ChunkSection *cs=it->second;
        if(cs==NULL)
            continue;
        if(it->first==dpos.y)
            return cs->mBlocks[dpos.x][dpos.z];
    }
    return BlockIdAndData{0,0};
}

void BaseChunk::updateBlock(glm::ivec3 bpos)
{
    prepareUpdate->push(bpos);
}



void BaseChunk::tick(float dtime)
{
    if(!prepareUpdate->empty()&&!updateing)
    {
        updateing=true;
        world->worldThreadPool->commit([this]
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
            updateing=false;
            //cond.notify_all();
        });
    }
}
