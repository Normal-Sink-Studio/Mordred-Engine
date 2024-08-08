#ifndef OpenGLServer
#define OpenGLServer

#pragma once
#include "flecs.h"
#include "renderComponents.hpp"

#include <cstddef>
#include <stdio.h> 
#ifdef _WIN32 
#include "Windows.h"
#include <GL/gl.h>
#elif __linux__
#include "X11/Xlib.h"

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#endif


namespace OpenGLRenderer
{
    void runSystems(ecs_world_t *world);
    void StartOpenGL(ecs_world_t *world);
    #pragma region Linux
    #ifdef __linux__
    void CreateContextLinux(ecs_iter_t *it);
    void RunOpenGLLinux(ecs_iter_t *it);
    void EndOpenGLLinux(ecs_iter_t *it);
    #endif
    #pragma endregion
    #pragma region Windows
    #ifdef WIN32
    void CreateContextWindows(ecs_iter_t *it);
    void SetWindowContext(WNDCLASS *wc, OpenGLWindows*);
    void RunOpenGLWindows(ecs_iter_t *it);
    void EndOpenGLWindows(ecs_iter_t *it);
    PIXELFORMATDESCRIPTOR* setPixelFormat();
    #endif
    #pragma endregion
}
#endif
