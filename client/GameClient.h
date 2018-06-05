#pragma once

#include <windows.h>
#include <winuser.h>
#include <time.h>

class gui;
class Player;
class GameWorld;
class GameRenderer;

class GameClient{
	public:
		HWND hwnd;
		HDC hdc;
		HGLRC hrc;
		gui* mGui;
		GameRenderer*mGameRenderer;
		Player*mPlayer;
		GameWorld* mWorld;
		float dtime;
		clock_t lasttime;
		int width,height;

		GameClient(HWND hwnd);
		~GameClient();
		void init();
		void tick();
		void setDC(HDC _hdc);
		void setwidthheight(int _width,int _height);
		void setWorld(GameWorld*_mWorld);
		void setMousePos(float x,float y);
		void setMouseVisibility(bool visibility);
		void Exit();
		gui* getGui();
		Player* getMainPlayer();
		GameWorld*getGameWorld();
		void onKeyBoard(int msg,int code);
		void onMouse(int msg);
		void onExit();
};
