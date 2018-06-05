#pragma once

#include "BaseScreen.h"
class TButton;

class PauseScreen:public BaseScreen{
public:
    TButton* mBackToGameButton,*mBackToTitleButton;

    PauseScreen(GameClient*gc);
    virtual ~PauseScreen();

    virtual void init();
    virtual void guiElementCallBack(int msg,GuiElement*mguielement);
    virtual void onKeyBoard(int msg,int code);
};
