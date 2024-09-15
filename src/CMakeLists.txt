cmake_minimum_required(VERSION "3.27.7")

project(Mordred-Engine)
set (Mordred-Engine_VERSION_MAJOR 0)
set (Mordred-Engine_VERSION_MINOR 0)
set (Mordred-Engine_VERSION_PATCH 0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)
find_package(OpenGL REQUIRED)

if (WIN32)
  # Windows-specific settings
  set(CMAKE_CXX_STANDARD 20)
  add_executable("Mordred-Engine" main.cpp Engine/engine.cpp Engine/Render/OpenGLServer.cpp)
  
  FetchContent_Declare(
    flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    GIT_TAG master
  )
  #FetchContent_Declare(
   # SDL
    #GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    #GIT_TAG master
  #)
  FetchContent_MakeAvailable(flecs)
  #FetchContent_MakeAvailable(SDL)
  target_include_directories(Mordred-Engine 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  )

  target_link_libraries(Mordred-Engine 
    PRIVATE flecs::flecs_static
    PRIVATE OpenGL::GL
    PRIVATE gdi32
  )
else()
  # Linux-specific settings
  find_package(X11 REQUIRED)
  
  set(CMAKE_CXX_STANDARD 17)
  add_executable("Mordred-Engine" main.cpp Engine/engine.cpp Engine/Render/OpenGLServer.cpp)
  
  FetchContent_Declare(
    flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    GIT_TAG master
  )
  
  FetchContent_MakeAvailable(flecs)
  
  target_include_directories(Mordred-Engine 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  )

  target_link_libraries(Mordred-Engine 
    PRIVATE flecs::flecs_static
    PRIVATE OpenGL::GL
    PRIVATE ${X11_LIBRARIES}
  )

  # Include X11 headers
  include_directories(${X11_INCLUDE_DIR})
endif()
