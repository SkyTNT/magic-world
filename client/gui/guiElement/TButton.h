#pragma once

#include <string>
#include "GuiElement.h"
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class TButton:public GuiElement{
public:
    std::string text_s;
    char* text;
    float textsize;
    bool pressing;
    glm::vec4 color;

    TButton(BaseScreen* _mScreen);
    virtual ~TButton();

    void setTextSize(float _size);
    void setText(std::string _text);

    virtual void render();
    virtual void onTouch(int msg,float mx,float my);
};
