#include "Dirt.h"
#include "../client/render/Texture.h"


Dirt::Dirt():Block("Dirt",1)
{
    tex1=blockTextures->subTexture(8.0f/32,12.0f/19,9.0f/32,13.0f/19);
}

Dirt::~Dirt()
{
    delete tex1;
}

Texture* Dirt::getTexture(unsigned int data)
{
    return tex1;
}

