
#include "pch.h"
#include "render_commandAPI.h"
#include "prime/renderer/renderer.h"

// platforms
#include "opengl/opengl_render_commandAPI.h"

namespace prime::renderer
{
	Scope<RenderCommandAPI> RenderCommandAPI::create()
	{
		switch (Renderer::getGraphicsAPI())
		{
		case graphicsAPI_opengl:
			return createScope<OpenGLRenderCommandAPI>();
			break;
		}
		return nullptr;
	}
}