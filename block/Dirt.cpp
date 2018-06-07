#include "Dirt.h"
#include "../client/render/Texture.h"


Dirt::Dirt():Block("Dirt",1)
{
    tex1=blockTextures->subTexture(8.0f/32,25.0f/32,9.0f/32,26.0f/32);
}

Dirt::~Dirt()
{
    delete tex1;
}

Texture* Dirt::getTexture(unsigned int data)
{
    return tex1;
}

