#pragma once

#include "prime/renderer/context.h"

namespace prime::renderer
{
	class OpenGLContext : public Context
	{
	private:
		WindowHandle m_window_handle = nullptr;
		ContextHandle m_handle = nullptr;

	public:
		OpenGLContext(WindowHandle handle);
		~OpenGLContext() override;

		void swapBuffers() override;
	};

	void createOpenGLDummyContext();
}