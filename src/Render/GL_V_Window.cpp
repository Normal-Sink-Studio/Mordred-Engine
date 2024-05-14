#include "GL_V_Window.hpp"

namespace Mordred
{
	GL_V_Window::GL_V_Window(int w, int h, std::string n) : width{w}, height{h}, windowName{n}
	{
		InitWindow(); //create the window
	}
	GL_V_Window::~GL_V_Window()
	{
		glfwDestroyWindow(glWindow); //destroy the window

		glfwTerminate(); //terminate all GLFW stuff
	}
	bool GL_V_Window::shouldClose() { 
		return glfwWindowShouldClose(glWindow);//check if the window is supposed to close
	}
	void GL_V_Window::InitWindow()
	{
		glfwInit(); //initialize GLFW
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //Set the GLFW Api to none
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); //set GLFW rezizable to true
		glWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr); //create the GLFW Window

	}
}