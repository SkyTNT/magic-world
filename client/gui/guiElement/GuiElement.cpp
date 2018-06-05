#include "GuiElement.h"
#include "../gui.h"
#include "../screen/BaseScreen.h"
#include "../../GameClient.h"
#include "../../../utils/Utils.h"

GuiElement::GuiElement(BaseScreen* _mScreen){
    mScreen=_mScreen;
    mGui=mScreen->client->getGui();
    x=0;
    y=0;
    width=1;
    height=1;
}
GuiElement::~GuiElement(){

}
void GuiElement::setWidth(float _width){
    width=_width;
}

void GuiElement::setHeight(float _height){
    height=_height;
}

void GuiElement::setX(float _x){
    x=_x;
}

void GuiElement::setY(float _y){
    y=_y;
}

void GuiElement::onTouch(int msg,float mx,float my){
}

