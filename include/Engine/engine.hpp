#ifndef engine
#define engine

#pragma once
#include<string>
#include "Render/OpenGLServer.hpp"
#include "flecs.h"
namespace Engine
{

		
		const int height = 600;//height
		const int width = 800;//width
		const std::string name = "Mordred Engine";// window name
		void run(); //function to run the window
	

}

#endif