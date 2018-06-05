#pragma once

class BlockShape
{
public:

    BlockShape();
    virtual ~BlockShape();

    virtual void init();
    //virtual void render();
    unsigned int vao,vbo,ebo;
};
