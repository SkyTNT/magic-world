#pragma once
#include "../guiElement/GuiElement.h"
#include <glm/vec4.hpp>
#include <vector>

#define KEYBOARD_UNKNOWN 0x00000000
#define KEYBOARD_KEYDOWN 0x00000001
#define KEYBOARD_KEYUP 0x00000002
#define KEYBOARD_KEY_WORD(w) 0x01000000+w
#define KEYBOARD_KEY_SHIFT 0x02000001
#define KEYBOARD_KEY_CTRL 0x02000003
#define KEYBOARD_KEY_SPACE 0x02000005
#define KEYBOARD_KEY_ESCAPE 0x02000006
#define KEYBOARD_KEY_F(index) 0x03000000+index
#define KEYBOARD_KEY_NUM(index) 0x04000000+index


class GameClient;

class BaseScreen{
public:
    enum{
    EVENT_MOUSE_LDOWN=0x00000001,
    EVENT_MOUSE_RDOWN=0x00000002,
    EVENT_MOUSE_LUP=0x00000003,
    EVENT_MOUSE_RUP=0x00000004,
    EVENT_MOUSE_MOVE=0x00000005
    };

    GameClient*client;
    std::vector<GuiElement*>guielements;
    GuiElement*pointedbymouse;
    glm::vec4 backgroundcolor;

    BaseScreen(GameClient*gc);
    virtual ~BaseScreen();

    virtual void init();
    virtual void tick(float dtime);
    virtual void render();
    virtual void guiElementCallBack(int msg,GuiElement*mguielement);
    virtual void setBackGroundColor(glm::vec4 color);
    virtual void addGuiElement(GuiElement* mguielement);
    virtual void onKeyBoard(int msg,int code);
    virtual void onMouse(int msg,float mx,float my);
    virtual void onExit();

};
