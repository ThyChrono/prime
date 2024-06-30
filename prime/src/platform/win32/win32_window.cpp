
#include "pch.h"
#include "prime/core/window.h"
#include "prime/core/events.h"
#include "prime/core/dispatcher.h"

// TODO: remove
#include <assert.h>

#ifdef PPLATFORM_WINDOWS

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace prime::core
{
	void Window::init(const WindowConfig& config)
	{
		HINSTANCE instance = GetModuleHandleA(nullptr);

		WNDCLASSEX wc{};
		wc.cbClsExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = LoadCursorA(instance, IDC_ARROW);
		wc.hIcon = LoadIconA(instance, IDI_WINLOGO);
		wc.hIconSm = LoadIconA(instance, IDI_WINLOGO);
		wc.hInstance = instance;
		wc.lpfnWndProc = wndProc;
		wc.lpszClassName = "PrimeWindowClass";
		wc.lpszMenuName = NULL;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

		auto atom = RegisterClassEx(&wc);
		assert(atom);

		DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		RECT rect = { 0, 0, (LONG)config.width, (LONG)config.height };
		AdjustWindowRect(&rect, style, false);

		HWND window = CreateWindowExA(NULL, MAKEINTATOM(atom), config.title.c_str(),
			style, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, instance, NULL);

		assert(window);
		ShowWindow(window, SW_SHOW);
		UpdateWindow(window);
		m_handle = window;

		// context
		m_context = renderer::Context::create(m_handle);
	}

	void Window::shutdown()
	{
		DestroyWindow((HWND)m_handle);
	}

	void Window::update()
	{
		m_context->swapBuffers();
	}

	void pollEvents()
	{
		MSG msg;
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	using namespace prime;

	switch (message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			core::Dispatcher::get().enqueue<core::WindowCloseEvent>(hWnd);
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif // PPLATFORM_WINDOWS