#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class World;

class Entity
{
public:
    glm::vec3 pos;
    glm::vec2 headRotate;
    Entity();
    virtual ~Entity();

    void setPos(glm::vec3 _pos);
    void setPos(float x,float y,float z);
    void moveBy(glm::vec3 dpos);
    void moveBy(float dx,float dy,float dz);
    void setHeadRotate(glm::vec2 hr);
    void setHeadRotate(float x,float y);
    void rotateHead(glm::vec2 dhr);
    void rotateHead(float dx,float dy);
    glm::vec3 getPos();
    glm::vec2 getHeadRotate();
    World *getRegion();
    void setRegion(World *_world);
private:
    World *world;
};
