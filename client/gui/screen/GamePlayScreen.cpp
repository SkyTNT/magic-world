#include "GamePlayScreen.h"
#include "../../GameClient.h"
#include "../guiElement/TButton.h"
#include "../../../utils/Utils.h"
#include "../../../entity/player/Player.h"
#include "../gui.h"
#include "../../../world/World.h"
#include "../../../world/chunk/Chunk.h"
#include <cstdlib>

#define M_PI  3.14159265358979323846264f

float mfps=0;
float frameNum=0,elapsedTime=0;

GamePlayScreen::GamePlayScreen(GameClient*gc):BaseScreen(gc)
{
    pressingkey[KEYBOARD_KEY_WORD('w')]=false;
    pressingkey[KEYBOARD_KEY_WORD('a')]=false;
    pressingkey[KEYBOARD_KEY_WORD('s')]=false;
    pressingkey[KEYBOARD_KEY_WORD('d')]=false;
    pressingkey[KEYBOARD_KEY_SHIFT]=false;
    pressingkey[KEYBOARD_KEY_SPACE]=false;
}

GamePlayScreen::~GamePlayScreen()
{

}

void GamePlayScreen::init()
{
    setBackGroundColor(glm::vec4(0,0,0,0));
    World*mWorld=client->getGameWorld();
    client->getMainPlayer()->setPos(glm::vec3(0,50,0));
    client->getMainPlayer()->setHeadRotate(0,0);
    client->setMousePos(client->width/2,client->height/2);
    client->setMouseVisibility(false);
}
#define PLAYER_SPEED 100.0f
void GamePlayScreen::tick(float dtime)
{
    elapsedTime+=dtime;
    frameNum++;
    if(elapsedTime>=0.5)
    {
        mfps=frameNum/elapsedTime;
        frameNum=0;
        elapsedTime=0;

    }
    Player *mp=client->getMainPlayer();

    if(pressingkey[KEYBOARD_KEY_WORD('w')])
    {
        mp->pos.x+=PLAYER_SPEED*dtime*sin(mp->headRotate.x);
        mp->pos.z+=PLAYER_SPEED*dtime*cos(mp->headRotate.x);
    }

    if(pressingkey[KEYBOARD_KEY_WORD('s')])
    {
        mp->pos.x+=PLAYER_SPEED*dtime*sin(mp->headRotate.x+M_PI);
        mp->pos.z+=PLAYER_SPEED*dtime*cos(mp->headRotate.x+M_PI);
    }

    if(pressingkey[KEYBOARD_KEY_WORD('a')])
    {
        mp->pos.x+=PLAYER_SPEED*dtime*sin(mp->headRotate.x+M_PI/2);
        mp->pos.z+=PLAYER_SPEED*dtime*cos(mp->headRotate.x+M_PI/2);
    }

    if(pressingkey[KEYBOARD_KEY_WORD('d')])
    {
        mp->pos.x+=PLAYER_SPEED*dtime*sin(mp->headRotate.x-M_PI/2);
        mp->pos.z+=PLAYER_SPEED*dtime*cos(mp->headRotate.x-M_PI/2);
    }


    if(pressingkey[KEYBOARD_KEY_SPACE])
        mp->pos.y+=PLAYER_SPEED*dtime;

    if(pressingkey[KEYBOARD_KEY_SHIFT])
        mp->pos.y-=PLAYER_SPEED*dtime;


}

void GamePlayScreen::render()
{
    BaseScreen::render();
    Player*mp=client->getMainPlayer();
    client->getGui()->drawText(5,client->height-25,20,glm::vec4(1,1,1,1),(char*)((("fps:"+f2s(mfps)).c_str())));
    client->getGui()->drawText(5,client->height-55,20,glm::vec4(1,1,1,1),(char*)((("player pos:"+f2s(mp->pos.x)+" "+f2s(mp->pos.y)+" "+f2s(mp->pos.z)).c_str())));
}

void GamePlayScreen::guiElementCallBack(int msg,GuiElement*mguielement)
{

}

void GamePlayScreen::onKeyBoard(int msg,int code)
{
    if(msg==KEYBOARD_KEYDOWN)
    {
        pressingkey[code]=true;
        if(code==KEYBOARD_KEY_ESCAPE)
        {
            client->setMouseVisibility(true);
            client->getGui()->pushPauseScreen();
        }

    }
    else if(msg==KEYBOARD_KEYUP)
    {
        pressingkey[code]=false;
    }

}

void GamePlayScreen::onMouse(int msg,float mx,float my)
{
    float cx=client->width/2;
    float cy=client->height/2;
    switch(msg)
    {
    case EVENT_MOUSE_MOVE:
    {
        Player*mplayer=client->getMainPlayer();
        glm::vec2 hr=mplayer->getHeadRotate();
        if(mx==cx&&my==cy)
            break;
        float rx=hr.x-(mx-cx)*0.01;
        float ry=hr.y;
        float _ry=hr.y+(my-cy)*0.01;
        if(!(_ry>=M_PI/2||_ry<=-M_PI/2))
            ry=_ry;

        mplayer->setHeadRotate(rx,ry);
        client->setMousePos(cx,cy);

        break;
    }
    /*case EVENT_MOUSE_LDOWN:
    {
        Player*mplayer=client->getMainPlayer();
        mplayer->placeBlock(glm::ivec3(mplayer->getPos()),{1,0});
        break;
    }*/

    }

}

void GamePlayScreen::onExit()
{
    client->setMouseVisibility(true);
}

