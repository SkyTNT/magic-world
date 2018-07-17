#pragma once
#include <glm/vec3.hpp>
#include "../BlockIdAndData.h"

class World;

class BlockShape
{
public:
    enum
    {
        SHAPE_NONE=0,
        SHAPE_CUBE=1
    };
    BlockShape();
    virtual ~BlockShape();

    virtual void init();
    virtual void addToWorld(World *world,glm::ivec3 bpos,glm::vec3 pos,BlockIdAndData idAndData);

    static void initBlockShapes();
    static void deleteBlockShapes();
    static BlockShape* mBlockShapes[1024];
};
