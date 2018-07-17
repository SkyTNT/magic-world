#pragma once
#include "../Entity.h"
#include "../../block/BlockIdAndData.h"

class Player:public Entity
{
public:
    Player();
    virtual ~Player();
    void destoryBlock(glm::ivec3 bpos);
    void placeBlock(glm::ivec3 bpos,BlockIdAndData idanddata);

};
