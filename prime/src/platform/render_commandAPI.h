#pragma once

#include "prime/core/defines.h"
#include "prime/maths/maths.h"

namespace prime::renderer {

	class RenderCommandAPI
	{
	public:
		virtual ~RenderCommandAPI() {}

		virtual void clear() = 0;
		virtual void clearColor(const maths::vec4& color) = 0;

		static Scope<RenderCommandAPI> create();
	};

}