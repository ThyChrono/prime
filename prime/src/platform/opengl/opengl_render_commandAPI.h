#pragma once

#include "platform/render_commandAPI.h"

namespace prime::renderer
{
	class OpenGLRenderCommandAPI : public RenderCommandAPI
	{
	public:
		void clear() override;
		void clearColor(const maths::vec4& color) override;
	};
}
