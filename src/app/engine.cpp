#include "engine.hpp"

namespace Mordred
{
	void engine::run() //run the engine
	{
		while(!window.shouldClose()) //check if the window needs to close
		{
			glfwPollEvents(); //keep it open if not
		}
	}
}