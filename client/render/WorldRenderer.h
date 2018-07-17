#pragma once

#include "../GameClient.h"
#include "RendererContext.h"
#include "Textures.h"


class WorldRenderer{
public:
    GameClient*  client;
    World*mWorld;
    Player* mPlayer;
    int width,height;
    RendererContext*context;

    GLuint blockShader;
    Textures* mTextures;

    WorldRenderer(GameClient*_client);
    ~WorldRenderer();
    void init();
    void setWorld(World* _mWorld);
    void setwidthheight(int _width,int _height);
    void setLookAt(glm::vec3 epos,glm::vec3 cpos,glm::vec3 upos);
    void tick(float dtime);
    void render();
};
