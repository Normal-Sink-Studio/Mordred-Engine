#include <string>

#ifdef _WIN32 
#include "Windows.h"
#include "GL/gl.h"
#elif __linux__
#include "X11/Xlib.h"
#include "GL/glx.h"
#endif

namespace Mordred
{
    namespace Components
    {
        struct Mesh{std::string path;}; //I will add actual mesh stuff later when

        #ifdef __linux__
        struct OpenGLLinux
        {
            Display *display;
            Window window;
            GLXContext glxContext;
            XEvent xevent;
            int displayStatus;
        };
        #elif WIN32
        struct OpenGLWindows
        {
            WNDCLASS windowClass;
            HDC hdc;
            HGLRC hRC;
            HWND hWnd;
            MSG msg;
            HINSTANCE hInstance;
            bool quit = false;
        };
        #endif
    }
}