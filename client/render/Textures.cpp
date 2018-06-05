#include "Textures.h"
#include <GL/gl3w.h>
#include <GL/wglext.h>
#include <Gl/gl.h>
#include <GL/glext.h>
#include "../../utils/Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../../stb/stb_image.h"

Textures::Textures(int _texnum)
{
    texnum=_texnum;
    textureIds=new GLuint[texnum];
    memset(textureIds,0,sizeof(GLfloat));

}

Textures::~Textures()
{
    glDeleteTextures(texnum,textureIds);
    delete[]textureIds;
}

void Textures::LoadTextureExt(int id,const char*filename)
{
    textureIds[id] = LoadTextureExt(filename);
}

GLuint Textures::LoadTextureExt(char const * filename)
{
    LOG_I(std::string(filename)+" load");
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format=GL_RGBA;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        LOG_I(std::string(filename)+" load failed");

        stbi_image_free(data);
    }

    return textureID;
}

GLuint Textures::getTexture(int id)
{
    return textureIds[id];
}
