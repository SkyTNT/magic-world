#pragma once

#include <string>
#include <vector>

struct BlockIdAndData
{
int id,data;
};

class BlockShape;

class Block
{
public:
    Block(std::string _name,int _id);
    virtual ~Block();

    virtual bool isSolid();
    virtual void getShape(int x,int y,int z,unsigned int data);
    virtual void init();

    static Block* mBlocks[1024];
    static void initBlocks();
protected:
    std::string name;
    int id;
    bool msolid;
    std::vector<BlockShape*>mShapes;
};

