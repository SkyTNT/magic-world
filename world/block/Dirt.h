#pragma once
#include "Block.h"

class Dirt:public Block
{
public:
    Dirt();
    virtual ~Dirt();
    virtual Texture* getTexture(unsigned int data);
private:
    Texture *tex1;
};
