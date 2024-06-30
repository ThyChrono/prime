
#include "pch.h"
#include "opengl_context.h"

#include <glad/glad.h>
#include <glad/glad_wgl.h>

namespace prime::renderer
{
	static u8 s_major_version = 0, s_minor_version = 0;

	OpenGLContext::OpenGLContext(WindowHandle handle)
	{
#ifdef PPLATFORM_WINDOWS

		PASSERT_MSG(handle, "Window is null");
		HDC device_context = GetDC(HWND(handle));

		PASSERT_MSG(s_major_version > 3 || (s_major_version == 4 && s_minor_version >= 3),
			"Prime requires at least OpenGL version 3.3!");

		int pixel_format_attribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		int pixel_format = 0;
		UINT pixel_format_id = 0;
		wglChoosePixelFormatARB(device_context, pixel_format_attribs, nullptr, 1, &pixel_format, &pixel_format_id);
		PASSERT(pixel_format_id);

		PIXELFORMATDESCRIPTOR pixel_format_desc = {};
		DescribePixelFormat(device_context, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pixel_format_desc);
		SetPixelFormat(device_context, pixel_format, &pixel_format_desc);

		int opengl_attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, s_major_version,
			WGL_CONTEXT_MINOR_VERSION_ARB, s_minor_version,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		m_handle = wglCreateContextAttribsARB(device_context, 0, opengl_attribs);
		PASSERT(m_handle);
		wglMakeCurrent(device_context, (HGLRC)m_handle);
		m_window_handle = handle;

#endif // PPLATFORM_WINDOWS
	}

	OpenGLContext::~OpenGLContext()
	{
#ifdef PPLATFORM_WINDOWS
		HWND window = (HWND)m_window_handle;
		HDC device_context = GetDC(window);
		HGLRC context = (HGLRC)m_handle;

		wglDeleteContext(context);
		ReleaseDC(window, device_context);
		DestroyWindow(window);
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::swapBuffers()
	{
#ifdef PPLATFORM_WINDOWS
		HDC device_context = GetDC(HWND(m_window_handle));
		SwapBuffers(device_context);
#endif // PPLATFORM_WINDOWS

	}

	void createOpenGLDummyContext()
	{
#ifdef PPLATFORM_WINDOWS

        WNDCLASSEX wc = {};
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = DefWindowProcA;
        wc.lpszClassName = "PrimeDummyWindow";
        wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = GetModuleHandleA(nullptr);

        ATOM atom = RegisterClassEx(&wc);
        PASSERT(atom);

        HWND dummy_window = CreateWindowEx( 0, MAKEINTATOM(atom), "PrimeDummyWindow",
            0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            0, 0, wc.hInstance, 0);

		PASSERT(dummy_window);

        HDC dummy_dc = GetDC(dummy_window);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.cColorBits = 32;
        pfd.cAlphaBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;

        int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
        SetPixelFormat(dummy_dc, pixel_format, &pfd);

        HGLRC dummy_context = wglCreateContext(dummy_dc);
		PASSERT(dummy_context);

        bool res = wglMakeCurrent(dummy_dc, dummy_context);
		PASSERT(res);

		u8 wgl_status = gladLoadWGL(dummy_dc);
		PASSERT(wgl_status);


		u8 gl_status = gladLoadGL();
		PASSERT(gl_status);

        wglMakeCurrent(dummy_dc, dummy_context);
		s_major_version = GLVersion.major;
		s_minor_version = GLVersion.minor;

        wglDeleteContext(dummy_context);
        ReleaseDC(dummy_window, dummy_dc);
        DestroyWindow(dummy_window);

#endif // PPLATFORM_WINDOWS

	}
}