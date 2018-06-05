#pragma once
#include <stack>
#include <map>
#include <string>
#include <glm/vec4.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class GameClient;
class BaseScreen;

struct Glyph;

class gui{
public:
    GameClient*client;
    std::stack<BaseScreen*>screenStack;
    FT_Library ftlib;
    FT_Face ftface;
    std::map<char, Glyph*> mGlyphs;

    unsigned int guiVao,guiVbo,guiShader;

    gui(GameClient*gc);
    ~gui();

    void init();
    void initGlyphs();
    void tick(float dtime);
    void render();

    void pushScreen(BaseScreen*screen);
    void pushPlayScreen();
    void pushGamePlayScreen();
    void pushPauseScreen();
    void popScreen();
    BaseScreen* getTopScreen();
    size_t getScreenNum();

    void drawTexture(float x,float y,float width,float height,float alpha,unsigned int tex);
    void drawRect(float x,float y,float width,float height,glm::vec4 color);
    void drawText(float x,float y,float msize,glm::vec4 color,char* text);
    glm::vec2 measureText(float msize,char* text);
};
