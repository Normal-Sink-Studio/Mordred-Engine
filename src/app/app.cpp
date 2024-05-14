#include <iostream>
#include <src/app/engine.hpp>

int main()
{
	Mordred::engine mEngine; //create engine object
	try //try running the enginee
	{
		mEngine.run(); //run the engine
	}
	catch (const std::exception& e) //otherwise retyrn a failure
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
