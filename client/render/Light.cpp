#include "Light.h"

Light::Light()
{
}

void Light::setLightColor(glm::vec3 _color)
{
    color=_color;
}

void Light::setPos(glm::vec3 _pos)
{
    pos=_pos;
}
