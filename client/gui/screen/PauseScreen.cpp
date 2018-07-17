#include "PauseScreen.h"
#include "../../GameClient.h"
#include "../guiElement/TButton.h"
#include "../../../utils/Utils.h"
#include "../gui.h"
#include "../../../world/World.h"

PauseScreen::PauseScreen(GameClient*gc):BaseScreen(gc)
{
    mBackToGameButton=new TButton(this);
    mBackToTitleButton=new TButton(this);
}

PauseScreen::~PauseScreen()
{
    delete mBackToGameButton;
    delete mBackToTitleButton;
}

void PauseScreen::init()
{
    float swidth=client->width;
    float sheight=client->height;
    mBackToGameButton->setX((swidth-250)/2);
    mBackToGameButton->setY((sheight-50)/2+30);
    mBackToGameButton->setWidth(250);
    mBackToGameButton->setHeight(50);
    mBackToGameButton->setText("back to game");
    addGuiElement(mBackToGameButton);
    mBackToTitleButton->setX((swidth-250)/2);
    mBackToTitleButton->setY((sheight-50)/2-30);
    mBackToTitleButton->setWidth(250);
    mBackToTitleButton->setHeight(50);
    mBackToTitleButton->setText("back to title");
    addGuiElement(mBackToTitleButton);

}

void PauseScreen::guiElementCallBack(int msg,GuiElement*mguielement)
{
    if(msg==GuiElement::GUICALLBACK_BUTTON_CLICK)
    {
        if(mguielement==mBackToGameButton)
        {
            client->setMouseVisibility(false);
            client->setMousePos(client->width/2,client->height/2);
            client->getGui()->popScreen();


        }
        else if(mguielement==mBackToTitleButton)
        {

            gui*mgui=client->getGui();
            delete client->mWorld;
            client->setWorld(NULL);
            while(mgui->getScreenNum()>1)
            {
                mgui->popScreen();
            }
        }
    }
}

void PauseScreen::onKeyBoard(int msg,int code)
{
    if(msg==KEYBOARD_KEYDOWN)
    {
        if(code==KEYBOARD_KEY_ESCAPE)
        {
            client->setMouseVisibility(false);
            client->setMousePos(client->width/2,client->height/2);
            client->getGui()->popScreen();
        }
    }
}
