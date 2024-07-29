#include "engine.hpp"
#include <iostream>

int main()
{
	 //create engine object
	try //try running the enginee
	{
		Mordred::run(); //run the engine
	}
	catch (const std::exception& e) //otherwise retyrn a failure
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
