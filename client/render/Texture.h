#pragma once

class Texture
{
public:
    unsigned int texid;
    float u1,v1,u2,v2;

    Texture(unsigned int _texid);
    ~Texture();

    Texture* subTexture(float  _u1,float _v1,float _u2,float _v2);
};
