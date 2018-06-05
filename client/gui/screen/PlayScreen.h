#pragma once

#include "BaseScreen.h"

class TButton;

class PlayScreen:public BaseScreen{
public:
    TButton*mPlayButton,*mExitButton;


    PlayScreen(GameClient*gc);
    virtual ~PlayScreen();

    virtual void init();
    virtual void guiElementCallBack(int msg,GuiElement*mguielement);
};
