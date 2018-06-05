#include "GameRenderer.h"
#include "../../utils/Utils.h"
#include "../gui/gui.h"

#define M_PI  3.14159265358979323846264f

GameRenderer::GameRenderer(GameClient* _client)
{
    client=_client;
    context=new RendererContext(client);
    mTextures=new Textures(1024);
    mWorldRenderer=new WorldRenderer(client);

}
GameRenderer::~GameRenderer()
{
    delete context;
    delete mWorldRenderer;
    delete mTextures;
}

void GameRenderer::init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    logfile<<glGetString(GL_VERSION)<<std::endl;
    logfile<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
    mWorldRenderer->init();

}

void GameRenderer::setwidthheight(int _width,int _height)
{
    width=_width;
    height=_height;
    glViewport(0, 0, width, height);
    context->proj = glm::perspective((float)(M_PI/4), (float)width/(float)height, 0.1f, 1000.0f);
    mWorldRenderer->setwidthheight(_width,_height);
}

void GameRenderer::tick(float dtime)
{
    render();
    mWorldRenderer->tick(dtime);
}

void GameRenderer::render()
{
    glClearColor(0.6f,0.9f,1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    mWorldRenderer->render();

    client->getGui()->render();
    SwapBuffers(client->hdc);
}

