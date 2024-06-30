#pragma once

#include "prime/core/defines.h"

namespace prime::renderer
{
	class Renderer2DAPI
	{
	public:
		virtual ~Renderer2DAPI() {}

		virtual void init(u32 max_sprites) = 0;
		virtual void shutdown() = 0;

		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void drawSprite(const maths::vec3& pos) = 0;

		static Scope<Renderer2DAPI> create();
	};
}
