#pragma once

#include <string>
#include <vector>
#include "BlockIdAndData.h"

class BlockShape;
class Texture;

class Block
{
public:
    Block(std::string _name,int _id);
    virtual ~Block();

    virtual bool isSolid();
    virtual BlockShape* getShape();
    virtual Texture* getTexture(unsigned int data);
    virtual void init();

    static Block* mBlocks[1024];
    static void initBlocks();
    static void deleteBlocks();
    static Texture* blockTextures;
protected:
    std::string name;
    int id;
    bool msolid;
};

