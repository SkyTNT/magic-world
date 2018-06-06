#pragma once
#include <stddef.h>
#include <vector>
#include <map>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

typedef int BufferID;

class ObjectGroup{
public:
    struct Buffer{
        size_t startVector,vectorCount;
    };
    unsigned int vao,vbo;
    ObjectGroup();
    ~ObjectGroup();
    void init();
    BufferID allocateBuffer(size_t vertexCount);
    int writeBuffer(Buffer traget,void* buff,size_t vertexCount);
    int translate(Buffer traget,glm::vec3 pos);
    int newCapacity(size_t vertexCount);
    Buffer getBuffer(BufferID id);
private:
    std::map<BufferID,Buffer>mBuffers;
    unsigned int mCapacity;
};
