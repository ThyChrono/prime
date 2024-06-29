#pragma once

#include "defines.h"

namespace prime::core {

	class WindowResizeEvent
	{
	private:
		u32 m_width = 0, m_height = 0;

	public:
		WindowResizeEvent(u32 width, u32 height)
			: m_width(width), m_height(height) {}

		u32 getWidth() const { return m_width; }
		u32 getHeight() const { return m_height; }
	};

	class WindowCloseEvent
	{
	private:
		WindowHandle m_handle = nullptr;

	public:
		WindowCloseEvent(WindowHandle handle) : m_handle(handle) {}

		const WindowHandle GetHandle() { return m_handle; }
	};
}