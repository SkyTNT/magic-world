#include "BlockObjectGroup.h"
#include "../Texture.h"

BlockObjectGroup::BlockObjectGroup():ObjectGroup()
{

}

BlockObjectGroup::~BlockObjectGroup()
{

}

void BlockObjectGroup::init()
{
ObjectGroup::init();
}

void BlockObjectGroup::addFace(float x1,float y1,float z1,float u1,float v1,float x2,float y2,float z2,float u2,float v2,float x3,float y3,float z3,float u3,float v3,Texture*tex)
{
    BufferID buffid=allocateBuffer(3);
    Buffer buff=getBuffer(buffid);
    glm::vec3 normal=glm::cross(glm::vec3(x2-x1,y2-y1,z2-z1),glm::vec3(x3-x1,y3-y1,z3-z1));
    float width=tex->u2-tex->u1;
    float heigh=tex->v2-tex->v1;
    float buffdata[3*8]= {x1,y1,z1,normal.x,normal.y,normal.z,u1*width+tex->u1,v1*heigh+tex->v1,
                          x2,y2,z2,normal.x,normal.y,normal.z,u2*width+tex->u1,v2*heigh+tex->v1,
                          x3,y3,z3,normal.x,normal.y,normal.z,u3*width+tex->u1,v3*heigh+tex->v1,
                         };
    writeBuffer(buff,buffdata,3);
}
