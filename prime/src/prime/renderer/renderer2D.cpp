
#include "pch.h"
#include "renderer2D.h"
#include "platform/renderer2DAPI.h"
#include "prime/core/dispatcher.h"
#include "prime/core/events.h"
#include "render_command.h"

namespace prime::renderer
{
	static Scope<Renderer2DAPI> s_API;

	static void OnWindowResize(const core::WindowResizeEvent& e)
	{
		u32 width = e.getWidth(), height = e.getHeight();
		if (width > 0 && height > 0)
		{
			RenderCommand::viewportResize(width, height);
		}
	}

	void Renderer2D::init(u32 max_sprites_per_draw)
	{
		if (!s_API) { s_API = Renderer2DAPI::create(); }
		s_API->init(max_sprites_per_draw);

		core::Dispatcher::get().sink<core::WindowResizeEvent>().connect<&OnWindowResize>();
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