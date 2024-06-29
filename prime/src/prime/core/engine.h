#pragma once

#include "game.h"
#include "window.h"

int main(int argc, char** argv);

namespace prime::core
{
	class Engine
	{
	private:
		struct Data
		{
			Window window;
		};

		static Data s_data;

	private:
		friend int::main(int argc, char** argv);

	private:
		static void run(Game* game);
	};
}