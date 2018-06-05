#pragma once

class gui;
class BaseScreen;

class GuiElement{
public:
    BaseScreen*mScreen;
    gui* mGui;
    float x,y,width,height;

    enum{
    EVENT_ACTIION_NONE=0x00000000,
    EVENT_ACTIION_LDOWN=0x00000001,
    EVENT_ACTIION_LUP=0x00000002,
    EVENT_ACTIION_RDOWN=0x00000003,
    EVENT_ACTIION_RUP=0x00000004,
    EVENT_ACTIION_MOVE=0x00000005,
    EVENT_ACTIION_MOVEIN=0x00000006,
    EVENT_ACTIION_MOVEOUT=0x00000007,

    GUICALLBACK_NONE=0x01000000,
    GUICALLBACK_BUTTON_CLICK=0x01000001
    };

    GuiElement(BaseScreen* _mScreen);
    virtual ~GuiElement();

    void setWidth(float _width);
    void setHeight(float _height);
    void setX(float _x);
    void setY(float _y);
    virtual void render()=0;
    virtual void onTouch(int msg,float mx,float my);

};
