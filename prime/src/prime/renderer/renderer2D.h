#pragma once

#include "prime/maths/maths.h"

namespace prime::renderer
{
	class Renderer2D
	{
	public:
		static void init();
		static void shutdown();

		static void begin();
		static void end();

		static void drawSprite(const scene::Transform& transform, const maths::vec4& color);
	};
}
