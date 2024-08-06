
#include "OpenGLServer.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>


using namespace OpenGLRenderer;
using namespace Mordred;
using namespace  Components;

void OpenGLRenderer::runSystems(ecs_world_t *world)
{
    
    OpenGLRenderer::StartOpenGL(world);
    //ECS_SYSTEM(world, Start, EcsOnStart);
}

void OpenGLRenderer::StartOpenGL(ecs_world_t *world)
{
    
    ecs_entity_t window = ecs_new(world);
    printf("Starting Render Engine\n");
    #ifdef _WIN32 
        printf("Initializing Engine in Windows Mode\n"); 
    #elif __linux__ 
        printf("Initializing Engine in Linux Mode\n"); 
        ECS_COMPONENT(world, OpenGLLinux);
        ecs_add(world, window, OpenGLLinux);
        ECS_SYSTEM(world, CreateContextLinux, EcsOnStart, OpenGLLinux);
        ECS_SYSTEM(world, RunOpenGLLinux, EcsOnUpdate, OpenGLLinux);
        
    #endif

    
}
#pragma region Linux
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
        0, 0, 800, 600, 0, 
        visualInfo->depth, 
        InputOutput, 
        visualInfo->visual, 
        CWColormap | CWEventMask,
        &setWindowAttributes
    );
    XStoreName(linuxContext->display, linuxContext->window, "Mordred Engine");
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
    OpenGLLinux *linuxContext = ecs_field(it, OpenGLLinux, 0);
    glXMakeCurrent(linuxContext->display, None, NULL);
    glXDestroyContext(linuxContext->display, linuxContext->glxContext);
    XCloseDisplay(linuxContext->display);
}
#pragma endregion
 