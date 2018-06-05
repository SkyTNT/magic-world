#include "RendererContext.h"
#include "../../utils/Utils.h"

RendererContext::RendererContext(GameClient*_client):client(_client){

}

void RendererContext::creatShader(GLuint*id,std::string path,GLenum type)
{
    *id=glCreateShader(type);
    std::string source;
    read_file(source,path);
    const GLchar* source_c=source.c_str();
    glShaderSource(*id, 1, &source_c, NULL);
    glCompileShader(*id);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*id, 512, NULL, infoLog);
        LOG_I("shader create failed: "+path+"\n"+infoLog+"\n"+source);
        return;
    }
}

void RendererContext::linkShader(GLuint*id,GLuint vs,GLuint fs)
{
    *id = glCreateProgram();
    glAttachShader(*id, vs);
    glAttachShader(*id, fs);
    glLinkProgram(*id);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(*id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(*id, 512, NULL, infoLog);
        LOG_I(std::string("shader link failed:\n")+infoLog);
        return;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
}
