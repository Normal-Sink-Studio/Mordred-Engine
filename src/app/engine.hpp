#pragma once
#include<src/Render/GL_V_Window.hpp>
#include<string>
namespace Mordred
{
	class engine
	{
	public:
		const int height = 600;//height
		const int width = 800;//width
		const std::string name = "Mordred Engine";// window name
		void run(); //function to run the window
	private:
		GL_V_Window window{width, height, name}; //create window object
	};

}