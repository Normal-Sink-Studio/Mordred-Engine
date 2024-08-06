#include "Engine/engine.hpp"
//#include "Render/OpenGLServer.hpp"
using namespace std;
#include <iostream>

int main()
{
	try //try running the enginee
	{
		 //run the engine
		 Engine::run();
	}
	catch (const std::exception& e) //otherwise retyrn a failure
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
