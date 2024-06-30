#pragma once

#include "defines.h"
#include "prime/renderer/context.h"

namespace prime::core {

	struct WindowConfig
	{
		u32 width = 0, height = 0;
		str title = "";
	};

	class Window
	{
	private:
		WindowConfig m_config;
		WindowHandle m_handle = nullptr;
		Scope<renderer::Context> m_context;

	public:
		void init(const WindowConfig& config);
		void shutdown();

		void update();
	};

	void pollEvents();
}
