#pragma once
#include <stddef.h>
#include <vector>
#include <map>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef int BufferID;

class Texture;

class ObjectGroup{
public:
    struct Buffer{
        size_t startVertex,vertexCount;
    };
    unsigned int vao,vbo,mVertexCount;
    glm::vec3 position;
    ObjectGroup();
    virtual ~ObjectGroup();
    virtual void init();
    BufferID allocateBuffer(size_t vertexCount);
    int writeBuffer(Buffer target,void* buff,size_t vertexCount);
    int translate(Buffer target,glm::vec3 pos);
    int newCapacity(size_t vertexCount);
    int useTexture(Buffer target,Texture* tex);
    Buffer getBuffer(BufferID id);
protected:
    std::map<BufferID,Buffer>mBuffers;
    void *bufferBuffer;
    unsigned int mVertexCapacity,mBufferBufferCapacity,bufferBufferVertexCount;
    BufferID lastID;
};
