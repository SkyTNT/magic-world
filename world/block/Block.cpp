#include "Block.h"
#include "Dirt.h"
#include "blockshape/BlockShape.h"
#include "../../client/render/Texture.h"
#include "../../client/render/Textures.h"

Block* Block::mBlocks[1024];
Texture* Block::blockTextures=0;

Block::Block(std::string _name,int _id):name(_name),id(_id)
{

}

Block::~Block()
{

}

void Block::initBlocks()
{
    blockTextures=new Texture(Textures::LoadTextureExt("assets\\blocktextures.png"));
    memset(mBlocks,0,sizeof(mBlocks));
    mBlocks[1]=new Dirt();
    mBlocks[1]->init();
}

void Block::deleteBlocks()
{
    for(Block* block:mBlocks)
        if(block!=NULL)delete block;

    delete blockTextures;
}

BlockShape* Block::getShape()
{
    return BlockShape::mBlockShapes[BlockShape::SHAPE_CUBE];
}

Texture* Block::getTexture(unsigned int data)
{
    return blockTextures;
}

bool Block::isSolid()
{
    return msolid;
}

void Block::init()
{

}
