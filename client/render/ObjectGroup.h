#pragma once
#include <stddef.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

class ObjectGroup{
public:
    struct Buffer{
        size_t startVector,vectorCount;
    };
    unsigned int vao,vbo;
    ObjectGroup();
    ~ObjectGroup();
    void init();
    Buffer allocateBuffer(size_t vertexCount);
    void addVertexBuffer(void* buff,size_t vertexCount);
    void translate(glm::vec3 pos);
    void resize(size_t vertexCount);
//private:
    size_t mSize;
    glm::mat4 model;
    unsigned int mCapacity,objCount;
};
