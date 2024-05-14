//#include<GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#pragma warning( push )
#pragma warning( disable : 4996 )
#include <vulkan/vulkan.hpp>
#pragma warning( push )
#include <iostream>
class Mordred
{
private:
	GLFWwindow* window;

	void initVulkan()
	{
		createInstance();

	}
	void createInstance() {

	}
	void initWindow()
	{
		glfwInit();
		//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(800, 600, "Mordred Engine", nullptr, nullptr);

		//if (glewInit != GLEW_OK)
		//{
			//std::cout << "ERROR!" << std::endl;
		//s}
	}
	void update()
	{
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window)) {
			//glClear(GL_COLOR_BUFFER_BIT);

			//glBegin(GL_TRIANGLES);
			//glVertex3f(-0.5f, -0.5f, -.5f);
			//glVertex3f(0.5f, .5f, 0.0);
			//glVertex3f(0.5f, -0.5f, 0.0f);
			//glEnd();

			glfwSwapBuffers(window);
			glfwPollEvents();
			glfwWaitEvents();
		}
	}
	void clean()
	{
		glfwDestroyWindow(window);

		glfwTerminate();
	}
public:
	void run()
	{
		//init vulkan for now but add openGL support later
		initWindow();
		update();
		clean();

	}
};

int main()
{
	Mordred mordred;

	try
	{
		mordred.run();
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
