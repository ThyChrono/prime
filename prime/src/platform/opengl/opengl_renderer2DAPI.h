#pragma once

#include "platform/renderer2DAPI.h"

namespace prime::renderer
{
	class OpenGLRenderer2DAPI : public Renderer2DAPI
	{
	public:
		~OpenGLRenderer2DAPI() override { shutdown(); }

		void init(u32 max_sprites) override;
		void shutdown() override;

		void begin() override;
		void end() override;

		void drawSprite(const scene::Transform& transform, const maths::vec4& color) override;

	private:
		void startBatch();
		void nextBatch();

		void initSpriteRendering();
	};
}