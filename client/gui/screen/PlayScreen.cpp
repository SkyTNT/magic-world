#include "PlayScreen.h"
#include "../gui.h"
#include "../../GameClient.h"
#include "../guiElement/TButton.h"
#include "../../../world/World.h"
#include "../../../world/generation/WorldGenerator.h"
#include "../../../world/chunk/Chunk.h"
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

void PlayScreen::guiElementCallBack(int msg,GuiElement*mguielement)
{
    if(msg==GuiElement::GUICALLBACK_BUTTON_CLICK)
    {
        if(mguielement==mPlayButton)
        {
            World*mWorld=new World(client);
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
