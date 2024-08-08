
#include "OpenGLServer.hpp"

#include "flecs.h"
#include "renderComponents.hpp"
#include <cstddef>
#include <stdio.h> 

using namespace OpenGLRenderer;
using namespace Mordred;
using namespace  Components;

void OpenGLRenderer::runSystems(ecs_world_t *world)
{
    
    OpenGLRenderer::StartOpenGL(world);
}

void OpenGLRenderer::StartOpenGL(ecs_world_t *world)
{
    
    ecs_entity_t window = ecs_new(world);
    printf("Starting Render Engine\n");
    #ifdef _WIN32 
        printf("Initializing Engine in Windows Mode\n"); 
        ECS_COMPONENT(world, OpenGLWindows);
        ecs_add(world, window, OpenGLWindows);
        ECS_SYSTEM(world, CreateContextWindows, EcsOnStart, OpenGLWindows);
        ECS_SYSTEM(world, RunOpenGLWindows, EcsOnUpdate, OpenGLWindows);
    #elif __linux__ 
        printf("Initializing Engine in Linux Mode\n"); 
        ECS_COMPONENT(world, OpenGLLinux);
        ecs_add(world, window, OpenGLLinux);
        ECS_SYSTEM(world, CreateContextLinux, EcsOnStart, OpenGLLinux);
        ECS_SYSTEM(world, RunOpenGLLinux, EcsOnUpdate, OpenGLLinux);
    #endif

    
}
#pragma region Linux
#ifdef __linux__
void OpenGLRenderer::CreateContextLinux(ecs_iter_t *it)
{
    printf("Creating Linux Context\n");
    OpenGLLinux *linuxContext = ecs_field(it, OpenGLLinux, 0);
    
    linuxContext->display = XOpenDisplay(NULL);
    if(!linuxContext-> display)
    {
        linuxContext->displayStatus = -1;
        return;
    }
    int screen = DefaultScreen(linuxContext -> display);
    int attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo *visualInfo = glXChooseVisual(linuxContext->display, screen, attributes);

    XSetWindowAttributes setWindowAttributes;
    setWindowAttributes.colormap = XCreateColormap(linuxContext->display, RootWindow(linuxContext->display, visualInfo->screen), visualInfo->visual,AllocNone);
    setWindowAttributes.event_mask = ExposureMask | KeyPressMask;
    
    linuxContext->window = XCreateWindow
    (
        linuxContext->display, 
        RootWindow(linuxContext->display, visualInfo->screen),
        0, 0, 1152, 648, 0, 
        visualInfo->depth, 
        InputOutput, 
        visualInfo->visual, 
        CWColormap | CWEventMask,
        &setWindowAttributes
    );
    XStoreName(linuxContext->display, linuxContext->window, "Mordred Engine");
    

    Atom wmState = XInternAtom(linuxContext->display, "_NET_WM_STATE", False);
    Atom maxH = XInternAtom(linuxContext->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    Atom maxV = XInternAtom(linuxContext->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

    XChangeProperty(linuxContext->display, linuxContext->window, wmState, XA_ATOM, 32, PropModeReplace, (unsigned char *)&maxH, 1);
    XChangeProperty(linuxContext->display, linuxContext->window, wmState, XA_ATOM, 32, PropModeAppend, (unsigned char *)&maxV, 1);

    XMapWindow(linuxContext->display,linuxContext->window);

    linuxContext->glxContext = glXCreateContext(linuxContext->display, visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(linuxContext->display,linuxContext->window, linuxContext->glxContext);
}

void OpenGLRenderer::RunOpenGLLinux(ecs_iter_t *it)
{
    OpenGLLinux *linuxContext = ecs_field(it, OpenGLLinux, 0);
    while(1)
    {
        XNextEvent(linuxContext->display, &linuxContext->xevent);
        if(linuxContext -> xevent.type == Expose)
        {
            //put rendering logic here
            
        }
        else if (linuxContext -> xevent.type == KeyPress) 
        {
            break;
        }
    }
    ECS_SYSTEM(it->world, EndOpenGLLinux, EcsOnSet, OpenGLLinux);
}

void OpenGLRenderer::EndOpenGLLinux(ecs_iter_t *it)
{
    OpenGLLinux *linuxContext;
    glXMakeCurrent(linuxContext->display, None, NULL);
    glXDestroyContext(linuxContext->display, linuxContext->glxContext);
    glXDestroyContext(linuxContext->display, linuxContext->glxContext);
    XCloseDisplay(linuxContext->display);
}
#endif
#pragma endregion
#pragma region Windows
#ifdef WIN32
void OpenGLRenderer::SetWindowContext(WNDCLASS* wc, OpenGLWindows* windowsContext)
{
    wc->style = CS_OWNDC;
    wc->lpfnWndProc = WndProc;
    wc->cbClsExtra = 0;
    wc->cbWndExtra = 0;
    wc->hInstance = windowsContext->hInstance;
    wc->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc->hCursor = LoadCursor(NULL, IDC_ARROW);
    wc->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc->lpszMenuName = NULL;
    wc->lpszClassName = "OpenGLWinClass";
}

void OpenGLRenderer::CreateContextWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext = ecs_field(it, OpenGLWindows, 0);
    SetWindowContext(windowsContext->windowClass, windowsContext);
    RegisterClass(windowsContext->windowClass);
    windowsContext->hWnd = CreateWindow(
        "OpenGLWinClass", "Mordred Engine",
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, windowsContext->hInstance, NULL);
    PIXELFORMATDESCRIPTOR* pixelFormatDescriptor = setPixelFormat();

    int pixelFormat = ChoosePixelFormat(windowsContext->hdc, pixelFormatDescriptor);
    SetPixelFormat(windowsContext->hdc, pixelFormat, pixelFormatDescriptor);

    windowsContext->hRC = wglCreateContext(windowsContext->hdc);
    wglMakeCurrent(windowsContext->hdc, windowsContext->hRC);

    ShowWindow(windowsContext->hWnd, SW_SHOW);
    UpdateWindow(windowsContext->hWnd);
}
PIXELFORMATDESCRIPTOR* OpenGLRenderer::setPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    return &pfd;

}
void OpenGLRenderer::RunOpenGLWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext= ecs_field(it, OpenGLWindows, 0);
    while(!windowsContext->quit)
    {
        if (PeekMessage(&windowsContext->msg, NULL, 0, 0, PM_REMOVE)) {
            if (windowsContext->msg.message == WM_QUIT) {
                windowsContext->quit = TRUE;
            } 
            else 
            {
                TranslateMessage(&windowsContext->msg);
                DispatchMessage(&windowsContext->msg);
            }
        } 
        else 
        {
            // OpenGL rendering code goes here
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Render scene
            SwapBuffers(windowsContext->hdc);
        }
    }
}
void OpenGLRenderer::EndOpenGLWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext = ecs_field(it, OpenGLWindows, 0);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(windowsContext->hRC);
    ReleaseDC(windowsContext->hWnd, windowsContext->hdc);
    DestroyWindow(windowsContext->hWnd);
    UnregisterClass("OpenGLWinClass", windowsContext->hInstance);
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        // Set the window to maximized state
        ShowWindow(hWnd, SW_MAXIMIZE);
        return 0;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_DESTROY:
        return 0;
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
#endif
#pragma endregion