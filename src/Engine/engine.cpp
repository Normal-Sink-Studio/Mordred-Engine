#include "engine.hpp"
using namespace Engine;

	void Engine::run() //run the engine
	{
		printf("Running Engine\n");
		ecs_world_t *world = ecs_init(); //creates the ECS world context
		
		OpenGLRenderer::runSystems(world);
		ecs_progress(world, 0);
	}
