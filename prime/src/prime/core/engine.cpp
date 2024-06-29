
#include "pch.h"
#include "engine.h"

namespace prime::core
{
	void Engine::run(Game* game)
	{
		game->init();

		game->update();

		game->shutdown();
	}
}