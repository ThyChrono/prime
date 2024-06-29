#pragma once

#include "defines.h"

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

	public:
		void init(const WindowConfig& config);
		void shutdown();
	};

	void pollEvents();
}
