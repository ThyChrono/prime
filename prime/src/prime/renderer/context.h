#pragma once

#include "prime/core/defines.h"

namespace prime::renderer
{
	class Context
	{
	public:
		virtual ~Context() {}

		virtual void swapBuffers() = 0;

		static Scope<Context> create(WindowHandle handle);
	};

	void createDummyContext();
}
