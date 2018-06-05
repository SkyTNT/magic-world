#pragma once

#include "GL/gl3w.h"
#include <GL/wglext.h>
#include <Gl/gl.h>
#include <GL/glext.h>
#include "Light.h"
#include <string>

class GameClient;

class RendererContext{
public:
    GameClient*client;
    glm::mat4 proj,view;
    Light light0;

    RendererContext(GameClient*_client);
    static void creatShader(GLuint*id,std::string path,GLenum type);
    static void linkShader(GLuint*id,GLuint vs,GLuint fs);

};
