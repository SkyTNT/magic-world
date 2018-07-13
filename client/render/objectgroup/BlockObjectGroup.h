#pragma once

#include "ObjectGroup.h"

class BlockObjectGroup:public ObjectGroup
{
public:
    BlockObjectGroup();
    virtual ~BlockObjectGroup();
    virtual void init();
    void addFace(float x1,float y1,float z1,float u1,float v1,float x2,float y2,float z2,float u2,float v2,float x3,float y3,float z3,float u3,float v3,Texture*tex);
};
