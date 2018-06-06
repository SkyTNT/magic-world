#include "main.h"
#include "GL/gl3w.h"
#include <GL/wglext.h>
#include <Gl/gl.h>
#include <GL/glext.h>
#include "utils/Utils.h"

GameClient*mGameClient=NULL;
HDC hdc;
HGLRC hrc;

bool InitializeOpenGL(HWND hwnd)
{
    PIXELFORMATDESCRIPTOR pfd;
    int result;
    int attributeList[5];

    hdc = GetDC (hwnd);


    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    if(!SetPixelFormat (hdc, ChoosePixelFormat (hdc, &pfd), &pfd))
        return false;

    hrc = wglCreateContext(hdc);
    if(!hrc)
    {
        return false;
    }
    if(!wglMakeCurrent(hdc, hrc))
    {
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if(!wglCreateContextAttribsARB)
    {
        return false;
    }

    gl3wInit();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);

    attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
    attributeList[1] = 1;
    attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
    attributeList[3] =1;

    attributeList[4] = 0;

    hrc = wglCreateContextAttribsARB(hdc, 0, attributeList);
    if(hrc == NULL)
    {
        return false;
    }

    result = wglMakeCurrent(hdc, hrc);
    if(result != 1)
    {
        return false;
    }

    return true;
}

void disableOpengl(HWND hwnd)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    ReleaseDC(hwnd,hdc);
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
    case WM_CREATE:
    {
        if(!InitializeOpenGL(hwnd))
        {
            MessageBox(NULL, "init opengl Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
            DestroyWindow(hwnd);
            break;
        }
        mGameClient=new GameClient(hwnd);
        mGameClient->setDC(hdc);
        mGameClient->hrc=hrc;
        mGameClient->init();
        break;
    }
    case WM_TIMER:
    {
        break;
    }

    case WM_SIZE:
    {
        break;
    }

    case WM_KEYDOWN:
    {
        mGameClient->onKeyBoard(Message,LOWORD(wParam));
        break;
    }

    case WM_KEYUP:
    {
        mGameClient->onKeyBoard(Message,LOWORD(wParam));
        break;
    }

    case WM_MOUSEMOVE:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_LBUTTONDOWN:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_RBUTTONDOWN:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_LBUTTONUP:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_RBUTTONUP:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_LBUTTONDBLCLK:
    {
        mGameClient->onMouse(Message);
        break;
    }

    case WM_RBUTTONDBLCLK:
    {
        mGameClient->onMouse(Message);
        break;
    }

    /* Upon destruction, tell the main thread to stop */
    case WM_DESTROY:
    {

        if(mGameClient!=NULL)
        {
            mGameClient->onExit();
        }
        if(hrc!=NULL)
            disableOpengl(hwnd);
        PostQuitMessage(0);
        break;
    }

    /* All other messages (a lot of them) are processed using default procedures */
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LOG_INIT();

    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG Msg; /* A temporary location for all messages */
    /* zero out the struct and set the stuff we want to modify */

    memset(&wc,0,sizeof(wc));
    wc.style       =CS_DBLCLKS;
    wc.cbSize		 = sizeof(WNDCLASSEX);
    wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
    wc.hInstance	 = hInstance;
    wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon		 = LoadIcon(hInstance,"APPICON"); /* Load a standard icon */
    wc.hIconSm		 = LoadIcon(hInstance,"APPICON"); /* use the name "A" to use the project icon */

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","magic world",WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                          CW_USEDEFAULT, /* x */
                          CW_USEDEFAULT, /* y */
                          1000, /* width */
                          618, /* height */
                          NULL,NULL,hInstance,NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }



    while(true)
    {
        if(PeekMessage (&Msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
            if(Msg.message == WM_QUIT)
                break;
        }
        if(mGameClient!=NULL)
            mGameClient->tick();

    }

    if(mGameClient!=NULL)
    {
        delete mGameClient;
    }
    LOG_FINIT();
    return Msg.wParam;
}
