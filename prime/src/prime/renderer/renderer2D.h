#pragma once

namespace prime::renderer
{
	class Renderer2D
	{
	public:
		static void init(u32 max_sprites_per_draw = 1000);
		static void shutdown();

		static void begin();
		static void end();

		static void drawSprite(const maths::vec3& pos, const maths::vec2& scale, f32 rotation, const maths::vec4& color);
	};
}
