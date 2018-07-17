#include "Entity.h"

Entity::Entity()
{
    pos=glm::vec3(0,0,0);
    headRotate=glm::vec2(0,0);
    world=NULL;
}

Entity::~Entity()
{

}

void Entity::setPos(glm::vec3 _pos)
{
    pos=_pos;
}

void Entity::setPos(float x,float y,float z)
{
    pos=glm::vec3(x,y,z);
}

void Entity::moveBy(glm::vec3 dpos)
{
    pos+=dpos;
}

void Entity::moveBy(float dx,float dy,float dz)
{
    pos+=glm::vec3(dx,dy,dz);
}

void Entity::setHeadRotate(glm::vec2 hr)
{
    headRotate=hr;
}

void Entity::setHeadRotate(float x,float y)
{
    headRotate=glm::vec2(x,y);
}

void Entity::rotateHead(glm::vec2 dhr)
{
    headRotate+=dhr;
}

void Entity::rotateHead(float dx,float dy)
{
    headRotate+=glm::vec2(dx,dy);
}

glm::vec3 Entity::getPos()
{
    return pos;
}

glm::vec2 Entity::getHeadRotate()
{
    return headRotate;
}

World* Entity::getRegion()
{
    return world;
}

void Entity::setRegion(World *_world)
{
    world=_world;
}
