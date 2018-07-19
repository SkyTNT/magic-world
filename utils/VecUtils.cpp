#include "VecUtils.h"

bool ivec3cmp::operator()(const glm::ivec3 &k1, const glm::ivec3 &k2)const
{
    if(k1.x<k2.x)
        return true;
    else if(k1.x>k2.x)return false;
    if(k1.y<k2.y)
        return true;
    else if(k1.y>k2.y)return false;
    if(k1.z<k2.z)
        return true;
    else if(k1.z>k2.z)return false;
    return false;
}

bool ivec2cmp::operator()(const glm::ivec2 &k1, const glm::ivec2 &k2)const
{
    if(k1.x<k2.x)
        return true;
    else if(k1.x>k2.x)return false;
    if(k1.y<k2.y)
        return true;
    else if(k1.y>k2.y)return false;
    return false;
}
