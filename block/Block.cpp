#include "Block.h"
#include "Dirt.h"
#include "../client/render/Texture.h"
#include "../client/render/Textures.h"

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
    mBlocks[1]=new Dirt();
    mBlocks[1]->init();
}

BlockShape* Block::getShape()
{
    return 0;
}

bool Block::isSolid()
{
    return msolid;
}

void Block::init()
{

}
