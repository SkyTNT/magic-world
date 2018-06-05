#pragma once
#include"BaseRenderer.h"
#include"Textures.h"
#include "Light.h"
#include <Saba\Model\MMD\MMDModel.h>
#include <Saba/Model/MMD/PMDModel.h>
#include <Saba/Model/MMD/PMXModel.h>

class MMDRenderer :public BaseRenderer
{
public :
    std::shared_ptr<saba::MMDModel> model;
    Textures*textures;
    size_t indexElemSize;
    GLenum m_indexType;
    GLuint vao,vboPos,vboNor,vboUV,ebo,shader;
    glm::mat4 modelmat;

    MMDRenderer(RendererContext*ctx);
    ~MMDRenderer();
    void setModel(std::shared_ptr<saba::MMDModel> _model);
    void setShader(GLuint sp);
    void updateMMD(float dtime);
    void setPos(glm::vec3 pos);
    virtual void init();
    virtual void tick(float dtime);
    virtual void render();
};
