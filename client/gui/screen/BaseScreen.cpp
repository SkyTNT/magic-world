#include "BaseScreen.h"
#include "../../GameClient.h"
#include "../gui.h"
#include "../../../utils/Utils.h"
#include "../guiElement/GuiElement.h"

BaseScreen::BaseScreen(GameClient*gc):client(gc)
{
    backgroundcolor=glm::vec4(0.2f, 0.3f, 0.3f, 0.5f);
    pointedbymouse=NULL;
}

BaseScreen::~BaseScreen()
{
   guielements.shrink_to_fit();
}

void BaseScreen::init()
{

}

void BaseScreen::tick(float dtime)
{

}

void BaseScreen::render()
{
    gui* mGui=client->getGui();

    mGui->drawRect(0,0,client->width,client->height,backgroundcolor);

    for(GuiElement*guielement:guielements)
    {
        guielement->render();
    }
}

void BaseScreen::guiElementCallBack(int msg,GuiElement*mguielement)
{

}

void BaseScreen::setBackGroundColor(glm::vec4 color)
{
    backgroundcolor=color;
}

void BaseScreen::addGuiElement(GuiElement* mguielement)
{
    guielements.push_back(mguielement);
}

void BaseScreen::onKeyBoard(int msg,int code)
{
}
void BaseScreen::onMouse(int msg,float mx,float my)
{
    size_t esize=guielements.size();
    for(unsigned int i=0; i<esize; i++)
    {
        GuiElement*ge=guielements[esize-i-1];
        if(ge==NULL)continue;
        if(ge->x<=mx&&ge->y<=my&&ge->x+ge->width>=mx&&ge->y+ge->height>=my)
        {
            if(pointedbymouse!=ge)
            {
                if(pointedbymouse!=NULL)
                    pointedbymouse->onTouch(GuiElement::EVENT_ACTIION_MOVEOUT,mx,my);
                ge->onTouch(GuiElement::EVENT_ACTIION_MOVEIN,mx,my);
            }
            pointedbymouse=ge;
            int tmsg=0;
            switch(msg)
            {
            case EVENT_MOUSE_LDOWN:
            {
                tmsg=GuiElement::EVENT_ACTIION_LDOWN;
                break;
            }

            case EVENT_MOUSE_LUP:
            {
                tmsg=GuiElement::EVENT_ACTIION_LUP;
                break;
            }

            case EVENT_MOUSE_RDOWN:
            {
                tmsg=GuiElement::EVENT_ACTIION_RDOWN;
                break;
            }

            case EVENT_MOUSE_RUP:
            {
                tmsg=GuiElement::EVENT_ACTIION_RUP;
                break;
            }

            case EVENT_MOUSE_MOVE:
            {
                tmsg=GuiElement::EVENT_ACTIION_MOVE;
                break;
            }

            default:
                break;
            }
            if(tmsg!=0)
                ge->onTouch(tmsg,mx,my);
        }
        else if(pointedbymouse==ge)
        {
            pointedbymouse=NULL;
            ge->onTouch(GuiElement::EVENT_ACTIION_MOVEOUT,mx,my);
        }

    }
}

void BaseScreen::onExit()
{

}
