#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace Mordred
{
	class GL_V_Window
	{
	public:
		GL_V_Window(int w, int h, std::string n); //construct object
		~GL_V_Window();//clear window
		bool shouldClose(); //check if the window is supposed to close

	private:

		void InitWindow(); //create the window
		const int width; //width
		const int height; //height
		std::string windowName; // window name
		GLFWwindow* glWindow; //GLFW window
	};
}