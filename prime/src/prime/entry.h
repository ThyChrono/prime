#pragma once

#include "core/engine.h"

#ifdef PPLATFORM_WINDOWS
int main(int argc, char** argv)
{
	using namespace prime;

	core::Game* game = core::createGame();
	core::Engine::run(game);

	delete game;
	game = nullptr;
	return 0;
}
#endif // PPLATFORM_WINDOWS
