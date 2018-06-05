#pragma once

#include "../GameClient.h"
#include "RendererContext.h"
#include "Textures.h"
#include "WorldRenderer.h"

class GameRenderer
{
public:
    GameClient*  client;
    int width,height;
    RendererContext*context;

    Textures* mTextures;
    WorldRenderer* mWorldRenderer;
    float rrr=0;

    GameRenderer(GameClient*_client);
    ~GameRenderer();

    void init();
    void setwidthheight(int _width,int _height);
    void tick(float dtime);
    void render();
};
