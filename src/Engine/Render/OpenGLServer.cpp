
#include "OpenGLServer.hpp"

#include "flecs.h"
#include "renderComponents.hpp"
#include <cstddef>
#include <stdio.h> 

#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h" // For modern OpenGL extensions
#include <GL/wglext.h>  // For WGL (Windows OpenGL) functions


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
#ifdef _WIN32

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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

GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
{
    // Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        MessageBoxA(0, infoLog, "ERROR: Vertex Shader Compilation Failed", 0);
    }

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        MessageBoxA(0, infoLog, "ERROR: Fragment Shader Compilation Failed", 0);
    }

    // Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        MessageBoxA(0, infoLog, "ERROR: Shader Program Linking Failed", 0);
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

PIXELFORMATDESCRIPTOR OpenGLRenderer::setPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd =
    {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
	PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
	32,                   // Colordepth of the framebuffer.
	0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0, 0, 0, 0,
	24,                   // Number of bits for the depthbuffer
	8,                    // Number of bits for the stencilbuffer
	0,                    // Number of Aux buffers in the framebuffer.
	PFD_MAIN_PLANE,
	0,
	0, 0, 0
    };
    return pfd;
}

void OpenGLRenderer::CreateContextWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext= ecs_field(it, OpenGLWindows, 0);

    const char CLASS_NAME[] = "Morded Window";

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    WNDCLASS wc = {0};

    wc.lpfnWndProc = WndProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx
    (
        CS_OWNDC,                                  // Optional window styles
        CLASS_NAME,                         // Window class name
        "Mordred Engine",                    // Window title
        WS_OVERLAPPEDWINDOW | WS_VISIBLE | 0x01000000L,                // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,       // Position (x, y)
        screenWidth, screenHeight,                           // Size (width, height)
        NULL,                               // Parent window
        NULL,                               // Menu
        wc.hInstance,                       // Instance handle
        NULL                                // Additional application data
    );

    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = setPixelFormat();
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
    
    HGLRC openGLContext = wglCreateContext(hdc);
    wglMakeCurrent(hdc, openGLContext);

    MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
    if(hwnd == NULL)
    {
        return;
    }

    ShowWindow(hwnd, SW_SHOW);

    windowsContext->hwnd = &hwnd;
}
//PIXELFORMATDESCRIPTOR* OpenGLRenderer::setPixelFormat()
///{

//}
void OpenGLRenderer::RunOpenGLWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext= ecs_field(it, OpenGLWindows, 0);
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
void OpenGLRenderer::EndOpenGLWindows(ecs_iter_t *it)
{
    OpenGLWindows* windowsContext = ecs_field(it, OpenGLWindows, 0);
}


#endif
#pragma endregion