#include "TButton.h"
#include "../screen/BaseScreen.h"
#include "../gui.h"
#include "../../../utils/UTILS.H"

TButton::TButton(BaseScreen* _mScreen):GuiElement(_mScreen)
{
    text=NULL;
    textsize=32;
    pressing=false;
    color=glm::vec4(0.2f, 0.3f, 0.3f,1);
}

TButton::~TButton()
{

}

void TButton::setTextSize(float _size)
{
    textsize=_size;
}

void TButton::setText(std::string _text)
{
    text_s=_text;
    text=(char*)text_s.c_str();
}

void TButton::render()
{
    mGui->drawRect(x,y,width,height,color);
    if(text!=NULL)
    {
        glm::vec2 textwh=mGui->measureText(textsize,text);
        mGui->drawText(x+(width-textwh.x)/2,y+(height-textwh.y)/2,textsize,glm::vec4(1,1,1,1),text);
    }
}

void TButton::onTouch(int msg,float mx,float my)
{
    switch(msg)
    {
    case EVENT_ACTIION_LDOWN:
    {
        pressing=true;
        color=glm::vec4(0.5f, 0.6f, 0.6f,1);
        break;
    }
    case EVENT_ACTIION_LUP:
    {
        if(pressing)
        {
            mScreen->guiElementCallBack(GUICALLBACK_BUTTON_CLICK,this);
        }
        pressing=false;
        color=glm::vec4(0.2f, 0.3f, 0.3f,1);
        break;
    }
    case EVENT_ACTIION_MOVEIN:
    {
        color=glm::vec4(0.3f, 0.4f, 0.4f,1);
        break;
    }
    case EVENT_ACTIION_MOVEOUT:
    {
        pressing=false;
        color=glm::vec4(0.2f, 0.3f, 0.3f,1);
        break;
    }
    }
}
