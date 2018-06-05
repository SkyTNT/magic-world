#pragma once
#include<windows.h>

class Textures
{
public:
    unsigned int* textureIds;
    int texnum;

    Textures(int _texnum);
    ~Textures();
    void LoadTextureExt(int id,const char*filename);
    static unsigned int LoadTextureExt(char const * filename);
    unsigned int getTexture(int id);
};
