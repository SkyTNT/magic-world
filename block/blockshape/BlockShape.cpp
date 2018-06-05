#include "BlockShape.h"
#include "../../client/render/RendererContext.h"

BlockShape::BlockShape()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    ebo=0;
}
BlockShape::~BlockShape()
{
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}

void BlockShape::init()
{
    GLfloat vertices[] =
    {
        0, 0, 0,0.0f,  0.0f, -1.0f,
        0,  1,0,0.0f,  0.0f, -1.0f,
        1,  1, 0,0.0f,  0.0f, -1.0f,
        1,  1, 0,0.0f,  0.0f, -1.0f,
        1, 0, 0,0.0f,  0.0f, -1.0f,
        0, 0, 0,0.0f,  0.0f, -1.0f,

        0, 0,  1,0.0f,  0.0f,  1.0f,
        1, 0,  1,0.0f,  0.0f,  1.0f,
        1,  1,  1, 0.0f,  0.0f,  1.0f,
        1,  1,  1, 0.0f,  0.0f,  1.0f,
        0,  1,  1, 0.0f,  0.0f,  1.0f,
        0, 0,  1, 0.0f,  0.0f,  1.0f,

        0,  1,  1,-1.0f,  0.0f,  0.0f,
        0,  1, 0,-1.0f,  0.0f,  0.0f,
        0, 0, 0, -1.0f,  0.0f,  0.0f,
        0, 0, 0, -1.0f,  0.0f,  0.0f,
        0, 0,  1, -1.0f,  0.0f,  0.0f,
        0,  1,  1, -1.0f,  0.0f,  0.0f,

        1,  1,  1, 1.0f,  0.0f,  0.0f,
        1, 0,  1, 1.0f,  0.0f,  0.0f,
        1, 0, 0,1.0f,  0.0f,  0.0f,
        1, 0, 0, 1.0f,  0.0f,  0.0f,
        1,  1, 0, 1.0f,  0.0f,  0.0f,
        1,  1,  1, 1.0f,  0.0f,  0.0f,

        0, 0, 0, 0.0f, -1.0f,  0.0f,
        1, 0, 0, 0.0f, -1.0f,  0.0f,
        1, 0, 1, 0.0f, -1.0f,  0.0f,
        1, 0,  1, 0.0f, -1.0f,  0.0f,
        0, 0,  1, 0.0f, -1.0f,  0.0f,
        0, 0, 0, 0.0f, -1.0f,  0.0f,

        0,  1, 0, 0.0f,  1.0f,  0.0f,
        0,  1,  1, 0.0f,  1.0f,  0.0f,
        1,  1, 1, 0.0f,  1.0f,  0.0f,
        1,  1,  1, 0.0f,  1.0f,  0.0f,
        1,  1, 0, 0.0f,  1.0f,  0.0f,
        0,  1, 0, 0.0f,  1.0f,  0.0f,
    };
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
