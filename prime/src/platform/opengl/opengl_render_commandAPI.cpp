
#include "pch.h"
#include "opengl_render_commandAPI.h"

#include <glad/glad.h>

namespace prime::renderer
{
	void OpenGLRenderCommandAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderCommandAPI::clearColor(const maths::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}