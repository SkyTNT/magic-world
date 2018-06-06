#include "PlayScreen.h"
#include "../gui.h"
#include "../../GameClient.h"
#include "../guiElement/TButton.h"
#include "../../../world/GameWorld.h"
#include "../../../world/generation/WorldGenerator.h"
#include "../../../world/chunk/BaseChunk.h"
#include "../../../utils/Utils.h"
#include "../../render/RendererContext.h"
#include <thread>

PlayScreen::PlayScreen(GameClient*gc):BaseScreen(gc)
{
    mPlayButton=new TButton(this);
    mExitButton=new TButton(this);
}

PlayScreen::~PlayScreen()
{
    delete mPlayButton;
    delete mExitButton;
}

void PlayScreen::init()
{
    float swidth=client->width;
    float sheight=client->height;
    mPlayButton->setX((swidth-200)/2);
    mPlayButton->setY((sheight-50)/2+30);
    mPlayButton->setWidth(200);
    mPlayButton->setHeight(50);
    mPlayButton->setText("play");
    addGuiElement(mPlayButton);
    mExitButton->setX((swidth-200)/2);
    mExitButton->setY((sheight-50)/2-30);
    mExitButton->setWidth(200);
    mExitButton->setHeight(50);
    mExitButton->setText("Exit");
    addGuiElement(mExitButton);


}
HGLRC hrc1=NULL;
/*void createWorldThread(GameClient*gc)
{
    wglMakeCurrent(gc->hdc,hrc1);

    GameWorld*mWorld=new GameWorld();
    mWorld->init(time(0));
    gc->getGui()->pushGamePlayScreen();
    gc->setWorld(mWorld);
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hrc1);

}*/

void PlayScreen::guiElementCallBack(int msg,GuiElement*mguielement)
{
    if(msg==GuiElement::GUICALLBACK_BUTTON_CLICK)
    {
        if(mguielement==mPlayButton)
        {
            /*hrc1=wglCreateContext(client->hdc);
            if(!wglShareLists(client->hrc,hrc1))LOG_I("err:"+i2s(GetLastError()));
            thread createworldtask(createWorldThread,client);
            createworldtask.detach();*/

            GameWorld*mWorld=new GameWorld(client);
            mWorld->init(time(0));
            mWorld->mainPlayer=client->getMainPlayer();
            client->setWorld(mWorld);
            client->getGui()->pushGamePlayScreen();

        }
        else if(mguielement==mExitButton)
        {
            client->Exit();
        }
    }
}
