#pragma once
#include <glm/vec3.hpp>

struct ivec3cmp{
bool operator()(const glm::ivec3 &k1, const glm::ivec3 &k2)const;
};

