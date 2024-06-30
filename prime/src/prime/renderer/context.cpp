
#include "pch.h"
#include "context.h"
#include "renderer.h"

// platforms
#include "platform/opengl/opengl_context.h"

namespace prime::renderer
{
	Scope<Context> Context::create(WindowHandle handle)
	{
		switch (Renderer::getGraphicsAPI())
		{
		case graphicsAPI_opengl:
			return createScope<OpenGLContext>(handle);
			break;
		}
		return nullptr;
	}

	void createDummyContext()
	{
		switch (Renderer::getGraphicsAPI())
		{
		case graphicsAPI_opengl:
			createOpenGLDummyContext();
			break;
		}
	}
}