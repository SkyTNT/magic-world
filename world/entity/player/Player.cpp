#include "Player.h"
#include "../../World.h"

Player::Player():Entity(){

}

Player::~Player()
{

}

void Player::destoryBlock(glm::ivec3 bpos)
{
    getRegion()->setBlock(bpos,{0,0});
}

void Player::placeBlock(glm::ivec3 bpos,BlockIdAndData idanddata)
{
    getRegion()->setBlock(bpos,idanddata);
}
