#include "GameClient.h"
#include "gui/gui.h"
#include "../entity/player/Player.h"
#include "../world/GameWorld.h"
#include "render/GameRenderer.h"
#include "../utils/Utils.h"
#include "gui/screen/BaseScreen.h"
#include "gui/screen/PlayScreen.h"
#include "../block/Block.h"
#include <math.h>
#include <stdlib.h>
#define VKW(a) a-32
#define M_PI  3.14159265358979323846264f

GameClient::GameClient(HWND hwnd)
{
    dtime=0;
    width=0;
    height=0;
    this->hwnd=hwnd;
    mGui=new gui(this);
    mPlayer=new Player();
    mWorld=NULL;
    mGameRenderer=new GameRenderer(this);
}

GameClient::~GameClient()
{
    delete mGui;
    delete mPlayer;
    delete mGameRenderer;
    if(mWorld!=NULL)delete mWorld;
}

void GameClient::init()
{
    lasttime=clock();
    RECT wr;
    GetClientRect(hwnd,&wr);
    setwidthheight(wr.right,wr.bottom);

    Block::initBlocks();
    mGui->init();
    mGui->pushPlayScreen();
    mGameRenderer->init();


}

void GameClient::tick()
{
    clock_t curtime=clock();
    dtime=curtime-lasttime;
    dtime/=1000;
    lasttime=curtime;
    mGui->tick(dtime);
    mGameRenderer->tick(dtime);
    if(mWorld!=NULL)mWorld->tick(dtime);
}

void GameClient::setDC(HDC _hdc)
{
    hdc=_hdc;
}

void GameClient::setWorld(GameWorld*_mWorld)
{
    mWorld=_mWorld;
    mGameRenderer->mWorldRenderer->setWorld(mWorld);
}

void GameClient::setMousePos(float x,float y)
{
    POINT mpos= {x,y};
    ClientToScreen(hwnd,&mpos);
    SetCursorPos(mpos.x,mpos.y);
}

void GameClient::setMouseVisibility(bool visibility)
{
    ShowCursor(visibility);
}

void GameClient::setwidthheight(int _width,int _height)
{
    width=_width;
    height=_height;
    mGameRenderer->setwidthheight(width,height);
}

void GameClient::Exit()
{
    DestroyWindow(hwnd);
}

gui* GameClient::getGui()
{
    return mGui;
}

Player* GameClient::getMainPlayer()
{
    return mPlayer;
}

GameWorld* GameClient::getGameWorld()
{
    return mWorld;
}

void GameClient::onKeyBoard(int msg,int code)
{
    if(mGui->getScreenNum()==0)
        return;

    int smsg=KEYBOARD_UNKNOWN,scode=KEYBOARD_UNKNOWN;
    switch(msg)
    {
    case WM_KEYDOWN:
    {
        smsg=KEYBOARD_KEYDOWN;
        break;
    }
    case WM_KEYUP:
    {
        smsg=KEYBOARD_KEYUP;
        break;
    }
    }

    switch(code)
    {
    case VK_SHIFT:
    {
        scode=KEYBOARD_KEY_SHIFT;
        break;
    }
    case VK_CONTROL:
    {
        scode=KEYBOARD_KEY_CTRL;
        break;
    }
    case VK_SPACE:
    {
        scode=KEYBOARD_KEY_SPACE;
        break;
    }

    case VK_ESCAPE:
    {
        scode=KEYBOARD_KEY_ESCAPE;
        break;
    }

    default:
    {
        if(code>=VKW('a')&&code<=VKW('z'))
        {
            scode=KEYBOARD_KEY_WORD(code+32);
        }
        else if(code>=VK_F1&&code<=VK_F19)
        {
            scode=KEYBOARD_KEY_F(code-VK_F1+1);
        }
        break;
    }
    }
    mGui->getTopScreen()->onKeyBoard(smsg,scode);
}

void GameClient::onMouse(int msg)
{
    if(mGui->getScreenNum()==0)
        return;

    POINT pt;
    GetCursorPos(&pt);

    ScreenToClient(hwnd,&pt);
    pt.y=height-pt.y;

    switch(msg)
    {
    case WM_MOUSEMOVE:
    {
        mGui->getTopScreen()->onMouse(BaseScreen::EVENT_MOUSE_MOVE,pt.x,pt.y);
        break;
    }

    case WM_LBUTTONDOWN:
    {
        mGui->getTopScreen()->onMouse(BaseScreen::EVENT_MOUSE_LDOWN,pt.x,pt.y);
        break;
    }

    case WM_RBUTTONDOWN:
    {
        mGui->getTopScreen()->onMouse(BaseScreen::EVENT_MOUSE_RDOWN,pt.x,pt.y);
        break;
    }

    case WM_LBUTTONUP:
    {
        mGui->getTopScreen()->onMouse(BaseScreen::EVENT_MOUSE_LUP,pt.x,pt.y);
        break;
    }

    case WM_RBUTTONUP:
    {
        mGui->getTopScreen()->onMouse(BaseScreen::EVENT_MOUSE_RUP,pt.x,pt.y);
        break;
    }

    default:
        break;
    }
}

void GameClient::onExit()
{

}
