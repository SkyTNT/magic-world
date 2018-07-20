#pragma once
#include "BlockShape.h"

class CubeBlockShape:public BlockShape
{
public:

    CubeBlockShape();
    virtual ~CubeBlockShape();

    virtual void init();

    virtual void addToWorld(World *world,glm::ivec3 bpos,glm::vec3 pos,BlockIdAndData idAndData);
private:
    float *vertices;
};

