#pragma once

#include "game.h"

int main(int argc, char** argv);

namespace prime::core
{
	class Engine
	{
	private:
		friend int::main(int argc, char** argv);

	private:
		static void run(Game* game);
	};
}