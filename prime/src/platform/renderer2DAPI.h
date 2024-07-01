#pragma once

#include "prime/core/defines.h"
#include "prime/scene/components.h"

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

		virtual void drawSprite(const scene::Transform& transform, const maths::vec4& color) = 0;

		static Scope<Renderer2DAPI> create();
	};
}
