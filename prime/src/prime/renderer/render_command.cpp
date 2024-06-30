
#include "pch.h"
#include "render_command.h"

// platform
#include "platform/render_commandAPI.h"

namespace prime::renderer
{
	static Scope<RenderCommandAPI> s_API;

	void RenderCommand::init()
	{
		if (!s_API) { s_API = RenderCommandAPI::create(); }
	}

	void RenderCommand::clear()
	{
		s_API->clear();
	}

	void RenderCommand::clearColor(const maths::vec4& color)
	{
		s_API->clearColor(color);
	}

	void RenderCommand::viewportResize(u32 width, u32 height)
	{
		s_API->viewportResize(width, height);
	}
}