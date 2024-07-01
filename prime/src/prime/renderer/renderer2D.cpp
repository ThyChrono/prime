
#include "pch.h"
#include "renderer2D.h"
#include "platform/renderer2DAPI.h"
#include "prime/core/dispatcher.h"
#include "prime/core/events.h"
#include "render_command.h"

#define MAX_SPRITES 10000

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

	void Renderer2D::init()
	{
		if (!s_API) { s_API = Renderer2DAPI::create(); }
		s_API->init(MAX_SPRITES);

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

	void Renderer2D::drawSprite(const scene::Transform& transform, const maths::vec4& color)
	{
		s_API->drawSprite(transform, color);
	}
}