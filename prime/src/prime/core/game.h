#pragma once

#include "defines.h"

namespace prime::core
{
	struct GameConfig
	{
		u32 width = 640, height = 480;
		str title = "Prime Game";
	};

	class Game
	{
	public:
		virtual void init() = 0;
		virtual void shutdown() = 0;

		virtual void update() = 0;
		virtual GameConfig GetConfig() { return GameConfig(); }
	};

	Game* createGame();
}
