#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
    glm::vec3 pos;
    glm::vec3 color;

    Light();
    void setLightColor(glm::vec3 _color);
    void setPos(glm::vec3 _pos);
};
