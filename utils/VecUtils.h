#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct ivec3cmp{
bool operator()(const glm::ivec3 &k1, const glm::ivec3 &k2)const;
};

struct ivec2cmp{
bool operator()(const glm::ivec2 &k1, const glm::ivec2 &k2)const;
};
