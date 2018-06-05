#include "gui.h"
#include "../GameClient.h"
#include "screen/BaseScreen.h"
#include "screen/PlayScreen.h"
#include "screen/GamePlayScreen.h"
#include "screen/PauseScreen.h"
#include "../render/RendererContext.h"
#include "../../utils/Utils.h"

struct Glyph
{
    GLuint     Texid;  // 字形纹理的ID
    glm::ivec2 Size;       // 字形大小
    glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
    GLuint     Advance;    // 原点距下一个字形原点的距离
};

gui::gui(GameClient*gc):client(gc)
{
}

gui::~gui()
{
    /*glDeleteVertexArrays(guiVao);
    glDeleteBuffers(guiVbo);
    glDeleteProgram(guiShader);*/
}

void gui::init()
{
    GLuint vs,fs;
    RendererContext::creatShader(&fs,"assets\\resource\\shader\\gui.frag",GL_FRAGMENT_SHADER);
    RendererContext::creatShader(&vs,"assets\\resource\\shader\\gui.vert",GL_VERTEX_SHADER);
    RendererContext::linkShader(&guiShader,vs,fs);

    GLfloat rectvert[] =
    {
        0, 0, 0, 0,
        1, 0, 1, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        0, 1, 0, 1,
        0, 0, 0, 0,
    };

    glGenVertexArrays(1, &guiVao);
    glGenBuffers(1, &guiVbo);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(guiVao);

    glBindBuffer(GL_ARRAY_BUFFER, guiVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectvert), rectvert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0);

    initGlyphs();
}

void gui::initGlyphs()
{
    if (FT_Init_FreeType(&ftlib))
        LOG_I("free type init failed");
    if (FT_New_Face(ftlib, "assets\\resource\\font\\font.ttf", 0, &ftface))
        LOG_I("ttf load failed");

    FT_Set_Pixel_Sizes(ftface, 0, 64);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
    for (BYTE c = 0; c < 128; c++)
    {
        // 加载字符的字形
        if (FT_Load_Char(ftface, c, FT_LOAD_RENDER))
        {
            LOG_I("load glyph "+c);
            continue;
        }
        // 生成纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ftface->glyph->bitmap.width,
            ftface->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ftface->glyph->bitmap.buffer
        );
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Glyph *mglyph =new Glyph;

        mglyph->Texid=texture;
        mglyph->Size=glm::ivec2(ftface->glyph->bitmap.width, ftface->glyph->bitmap.rows);
        mglyph->Bearing=glm::ivec2(ftface->glyph->bitmap_left, ftface->glyph->bitmap_top);
        mglyph->Advance=ftface->glyph->advance.x;

        mGlyphs[c]=mglyph;
    }
}

void gui::tick(float dtime)
{
    if(getScreenNum()==0)return;

    getTopScreen()->tick(dtime);
}
void gui::render()
{
    if(getScreenNum()==0)return;

    glDisable(GL_DEPTH_TEST);
    getTopScreen()->render();
    glEnable(GL_DEPTH_TEST);
}

void gui::pushScreen(BaseScreen*screen)
{
    screenStack.push(screen);
}

void gui::pushPlayScreen()
{
    PlayScreen *screen=new PlayScreen(client);
    screen->init();
    pushScreen(screen);
}

void gui::pushGamePlayScreen()
{
    GamePlayScreen *screen=new GamePlayScreen(client);
    screen->init();
    pushScreen(screen);
}

void gui::pushPauseScreen()
{
    PauseScreen *screen=new PauseScreen(client);
    screen->init();
    pushScreen(screen);
}

BaseScreen* gui::getTopScreen()
{
    return screenStack.top();
}

void gui::popScreen()
{
    getTopScreen()->onExit();
    delete getTopScreen();
    screenStack.pop();
}

size_t gui::getScreenNum()
{
    return screenStack.size();
}

void gui::drawTexture(float x,float y,float width,float height,float alpha,unsigned int tex)
{
    int swidth,sheight;
    swidth=client->width;
    sheight=client->height;
    glUseProgram(guiShader);
    glBindVertexArray(guiVao);
    glm::mat4 posmat;
    posmat=glm::translate(posmat,glm::vec3(x*2/swidth-1,y*2/sheight-1,0));
    posmat=glm::scale(posmat,glm::vec3(width*2/swidth,height*2/sheight,1));
    glUniformMatrix4fv(glGetUniformLocation(guiShader, "posmat"), 1, GL_FALSE, glm::value_ptr(posmat));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(glGetUniformLocation(guiShader, "mTexture"), 0);
    glUniform1i(glGetUniformLocation(guiShader, "type"), 0);
    glUniform1i(glGetUniformLocation(guiShader, "useTexture"), 1);
    glUniform4fv(glGetUniformLocation(guiShader, "useColor"), 1,glm::value_ptr(glm::vec4(1,1,1,alpha)));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void gui::drawRect(float x,float y,float width,float height,glm::vec4 color)
{
    int swidth,sheight;
    swidth=client->width;
    sheight=client->height;
    glUseProgram(guiShader);
    glBindVertexArray(guiVao);
    glm::mat4 posmat;
    posmat=glm::translate(posmat,glm::vec3(x*2/swidth-1,y*2/sheight-1,0));
    posmat=glm::scale(posmat,glm::vec3(width*2/swidth,height*2/sheight,1));
    glUniformMatrix4fv(glGetUniformLocation(guiShader, "posmat"), 1, GL_FALSE, glm::value_ptr(posmat));
    glUniform1i(glGetUniformLocation(guiShader, "type"), 0);
    glUniform1i(glGetUniformLocation(guiShader, "useTexture"), 0);
    glUniform4fv(glGetUniformLocation(guiShader, "useColor"), 1,glm::value_ptr(color));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void gui::drawText(float x,float y,float msize,glm::vec4 color,char* text)
{
    size_t textsize=strlen(text);
    for(unsigned int i=0; i<textsize; i++)
    {
        Glyph* mglyph=NULL;
        mglyph=mGlyphs[text[i]];

        if(!mglyph)
        {
            x+=msize;
            continue;
        }

        float xpos = x + mglyph->Bearing.x * msize/64;
        float ypos = y - (mglyph->Size.y - mglyph->Bearing.y) * msize/64;

        int swidth,sheight;
        swidth=client->width;
        sheight=client->height;
        glUseProgram(guiShader);
        glBindVertexArray(guiVao);
        glm::mat4 posmat;
        posmat=glm::translate(posmat,glm::vec3(xpos*2/swidth-1,ypos*2/sheight-1,0));
        posmat=glm::scale(posmat,glm::vec3(mglyph->Size.x*msize/(32*swidth),mglyph->Size.y*msize/(32*sheight),1));
        glUniformMatrix4fv(glGetUniformLocation(guiShader, "posmat"), 1, GL_FALSE, glm::value_ptr(posmat));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,mglyph->Texid);
        glUniform1i(glGetUniformLocation(guiShader, "mTexture"), 0);
        glUniform1i(glGetUniformLocation(guiShader, "type"), 1);
        glUniform1i(glGetUniformLocation(guiShader, "useTexture"), 1);
        glUniform4fv(glGetUniformLocation(guiShader, "useColor"), 1,glm::value_ptr(color));

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        x+=(mglyph->Advance >> 6) * msize/64;

    }

}

glm::vec2 gui::measureText(float msize,char* text){
    float textwidth=0,textheight=0;
    size_t textsize=strlen(text);
    for(unsigned int i=0; i<textsize; i++)
    {
        Glyph* mglyph=NULL;
        mglyph=mGlyphs[text[i]];

        if(!mglyph)
        {
            textwidth+=msize;
            continue;
        }
        float _height=mglyph->Bearing.y * msize/64;
        if(textheight<_height)textheight=_height;

        textwidth+=(mglyph->Advance >> 6) * msize/64;

    }
    return glm::vec2(textwidth,textheight);
}
