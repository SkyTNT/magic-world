#include "BaseChunk.h"
#include "../GameWorld.h"
#include "../../block/blockshape/BlockShape.h"
#include "../../client/render/ObjectGroup.h"
#include <glm/vec3.hpp>
BaseChunk::BaseChunk(GameWorld* _world)
{
    world=_world;
    objGroup=new ObjectGroup();
    objGroup->init();
    prepareUpdate=new std::queue<glm::ivec3>();
}

BaseChunk::~BaseChunk()
{
    delete objGroup;
    mBlocks.clear();
    delete prepareUpdate;
}

void BaseChunk::setPos(glm::ivec3 _pos)
{
    pos=_pos;
    objGroup->position=_pos;
}

void BaseChunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    BlockIdAndData idanddata= {id,data};
    mBlocks[bpos]=BlockInfo{idanddata,0};
    updateBlock(bpos);
}
void BaseChunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}

void BaseChunk::updateBlock(glm::ivec3 bpos)
{
    prepareUpdate->push(bpos);
}

void BaseChunk::tick(float dtime)
{
    glm::ivec3 ubpos;
    while(prepareUpdate->size()>0)
    {
        /*hrc1=wglCreateContext(client->hdc);
        if(!wglShareLists(client->hrc,hrc1))LOG_I("err:"+i2s(GetLastError()));
        thread updateblockthread(updateblocktask,client);
        updateblockthread.detach();*/

        ubpos=prepareUpdate->front();
        prepareUpdate->pop();
        auto it=mBlocks.find(ubpos);
        if(it==mBlocks.end())
            continue;
        BlockIdAndData idanddata=it->second.idanddata;
        Block::mBlocks[idanddata.id]->getShape()->addToWorld(world,ubpos,glm::vec3(ubpos),idanddata,it->second.buffid);
    }
    delete prepareUpdate;
    prepareUpdate=new std::queue<glm::ivec3>();
}
