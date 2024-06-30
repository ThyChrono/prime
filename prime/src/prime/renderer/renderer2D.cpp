
#include "pch.h"
#include "renderer2D.h"
#include "platform/renderer2DAPI.h"

namespace prime::renderer
{
	static Scope<Renderer2DAPI> s_API;

	void Renderer2D::init(u32 max_sprites_per_draw)
	{
		if (!s_API) { s_API = Renderer2DAPI::create(); }
		s_API->init(max_sprites_per_draw);
	}

	void Renderer2D::shutdown()
	{
		s_API->shutdown();
	}

	void Renderer2D::begin()
	{
		s_API->begin();
	}

	void Renderer2D::end()
	{
		s_API->end();
	}

	void Renderer2D::drawSprite(const maths::vec3& pos)
	{
		s_API->drawSprite(pos);
	}
}