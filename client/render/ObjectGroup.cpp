#include "ObjectGroup.h"
#include "RendererContext.h"
#include "../../utils/Utils.h"

#define STEP_LONG 6*sizeof(float)

ObjectGroup::ObjectGroup()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    mSize=0;
    mCapacity=0;
    objCount=0;
}

ObjectGroup::~ObjectGroup()
{
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}

void ObjectGroup::init()
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 16*16*36*STEP_LONG,0 , GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STEP_LONG, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STEP_LONG, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
ObjectGroup::Buffer ObjectGroup::allocateBuffer(size_t vertexCount)
{

}

void ObjectGroup::addVertexBuffer(void *buff,size_t vertexCount)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    void* vboptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if(vboptr==0)return;
    memcpy(vboptr+mSize,buff,vertexCount*STEP_LONG);
    for(int i=0;i<vertexCount;i++)
    {
        glm::vec3* vertexpos=(glm::vec3*)(vboptr+mSize+i*STEP_LONG);
        glm::vec4 result=glm::vec4(*vertexpos,1);
        result=model*result;
        *vertexpos=glm::vec3(result);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    mSize+=vertexCount*STEP_LONG;
    objCount++;
}

void ObjectGroup::translate(glm::vec3 pos)
{
    glm::mat4 _model;
    _model = glm::translate(_model,pos);
    model=_model;
}

void ObjectGroup::resize(size_t vertexCount)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*STEP_LONG,0 , GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
