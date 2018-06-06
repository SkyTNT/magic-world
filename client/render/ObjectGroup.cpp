#include "ObjectGroup.h"
#include "RendererContext.h"
#include "../../utils/Utils.h"

#define STEP_LONG 6*sizeof(float)

ObjectGroup::ObjectGroup()
{
    vao=0;
    vbo=0;
    mVertexCapacity=0;
    lastID=0;
    mVertexCount=0;
    position=glm::vec3();
}

ObjectGroup::~ObjectGroup()
{
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}

void ObjectGroup::init()
{
newCapacity(16*16*36);
}
BufferID ObjectGroup::allocateBuffer(size_t vertexCount)
{
    if(mVertexCount+vertexCount>mVertexCapacity)
    {
        int result=newCapacity(mVertexCount+vertexCount+16*16*36);
        if(result<0)LOG_I("allocate buffer err:"+i2s(result));
    }

    lastID++;
    mBuffers[lastID]=ObjectGroup::Buffer{mVertexCount,vertexCount};
    mVertexCount+=vertexCount;
    return lastID;
}

int ObjectGroup::writeBuffer(Buffer target,void* buff,size_t vertexCount)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    void* vboptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if(vboptr==0)return -1;
    memcpy(vboptr+target.startVertex*STEP_LONG,buff,target.vertexCount*STEP_LONG);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 0;
}

int ObjectGroup::translate(Buffer target,glm::vec3 pos)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    void* vboptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if(vboptr==0)return -1;
    glm::mat4 model;
    model = glm::translate(model,pos);
    for(int i=0;i<target.vertexCount;i++)
    {
        glm::vec3* vertexpos=(glm::vec3*)(vboptr+(target.startVertex+i)*STEP_LONG);
        glm::vec4 result=glm::vec4(*vertexpos,1);
        result=model*result;
        *vertexpos=glm::vec3(result);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 0;
}

ObjectGroup::Buffer ObjectGroup::getBuffer(BufferID id)
{
    auto it=mBuffers.find(id);
    return it==mBuffers.end()?ObjectGroup::Buffer{0,0}:it->second;
}

int ObjectGroup::newCapacity(size_t vertexCount)
{
    unsigned int _vao,_vbo;

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*STEP_LONG,0 , GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STEP_LONG, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STEP_LONG, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    if(vbo==0)
    {
        vao=_vao;
        vbo=_vbo;
        mVertexCapacity=vertexCount;
        return 0;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    void* _vboptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if(_vboptr==0)return -1;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    void* vboptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if(vboptr==0)return -2;
    memcpy(_vboptr,vboptr,mVertexCapacity*STEP_LONG);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);

    vao=_vao;
    vbo=_vbo;
    mVertexCapacity=vertexCount;
    return 0;
}
