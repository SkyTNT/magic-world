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

}

BaseChunk::~BaseChunk()
{
    delete objGroup;
    mBlocks.clear();
}

void BaseChunk::setPos(glm::ivec3 _pos)
{
    pos=_pos;
    objGroup->position=_pos;
}

void BaseChunk::setBlock(glm::ivec3 bpos,int id,int data)
{
    BlockIdAndData idanddata={id,data};
    mBlocks[bpos]=idanddata;
    Block::mBlocks[id]->getShape()->addToWorld(world,bpos,glm::vec3(bpos),idanddata);
}
void BaseChunk::setBlock(int x,int y,int z,int id,int data)
{
    setBlock(glm::ivec3(x,y,z),id,data);
}
