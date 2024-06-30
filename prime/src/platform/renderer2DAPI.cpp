
#include "pch.h"
#include "renderer2DAPI.h"
#include "prime/renderer/renderer.h"

// platforms
#include "opengl/opengl_renderer2DAPI.h"

namespace prime::renderer
{
	Scope<Renderer2DAPI> Renderer2DAPI::create()
	{
		switch (Renderer::getGraphicsAPI())
		{
		case graphicsAPI_opengl:
			return createScope<OpenGLRenderer2DAPI>();
			break;
		}
		return nullptr;
	}
}