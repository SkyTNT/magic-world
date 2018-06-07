#include "Texture.h"

Texture::Texture(unsigned int _texid)
{
    texid=_texid;
    u1=0.0f;
    v1=0.0f;
    u2=1.0f;
    v2=1.0f;
}

Texture::~Texture()
{

}

Texture* Texture::subTexture(float  _u1,float _v1,float _u2,float _v2)
{
    float width=u2-u1;
    float heigh=v2-v1;
    Texture*tex=new Texture(texid);
    tex->u1=u1+width*_u1;
    tex->v1=v1+heigh*_v1;
    tex->u2=u1+width*_u2;
    tex->v2=v1+heigh*_v2;

    return tex;
}
