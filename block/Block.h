#pragma once

#include <string>
#include <vector>

struct BlockIdAndData
{
int id,data;
};

class BlockShape;
class Texture;

class Block
{
public:
    Block(std::string _name,int _id);
    virtual ~Block();

    virtual bool isSolid();
    virtual BlockShape* getShape();
    virtual void init();

    static Block* mBlocks[1024];
    static void initBlocks();
    static Texture* blockTextures;
protected:
    std::string name;
    int id;
    bool msolid;
};

