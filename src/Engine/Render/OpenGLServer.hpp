#pragma once
#include "flecs.h"
#include "components.hpp"
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstddef>
#include <stdio.h> 
#ifdef _WIN32 
#include "windows.h"
#elif __linux__
#include "X11/Xlib.h"
#endif

namespace OpenGLRenderer
{
    void runSystems(ecs_world_t *world);
    void StartOpenGL(ecs_world_t *world);
    void CreateContextLinux(ecs_iter_t *it);
    void RunOpenGLLinux(ecs_iter_t *it);
    void EndOpenGLLinux(ecs_iter_t *it);
    void Test();
}
