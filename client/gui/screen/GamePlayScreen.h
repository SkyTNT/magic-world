#pragma once

#include "BaseScreen.h"
#include <map>

class TButton;

class GamePlayScreen:public BaseScreen{
public:
    std::map<int,bool> pressingkey;

    GamePlayScreen(GameClient*gc);
    virtual ~GamePlayScreen();

    virtual void init();
    virtual void tick(float dtime);
    virtual void render();
    virtual void guiElementCallBack(int msg,GuiElement*mguielement);
    virtual void onKeyBoard(int msg,int code);
    virtual void onMouse(int msg,float mx,float my);
    virtual void onExit();

};
