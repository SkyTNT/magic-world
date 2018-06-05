#include "Block.h"
#include "Dirt.h"

Block* Block::mBlocks[1024];

Block::Block(std::string _name,int _id):name(_name),id(_id)
{

}

Block::~Block()
{

}

void Block::initBlocks()
{
    mBlocks[1]=new Dirt();
    mBlocks[1]->init();
}

void Block::getShape(int x,int y,int z,unsigned int data){

}

bool Block::isSolid()
{
    return msolid;
}

void Block::init()
{

}
