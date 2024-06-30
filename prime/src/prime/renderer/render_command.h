#pragma once

#include "prime/maths/maths.h"

namespace prime::renderer
{
	class RenderCommand
	{
	public:
		static void init();

		static void clear();
		static void clearColor(const maths::vec4& color);
	};
}
