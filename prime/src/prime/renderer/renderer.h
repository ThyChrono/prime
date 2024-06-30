#pragma once

namespace prime::renderer
{
	enum GraphicsAPI
	{
		graphicsAPI_opengl
	};

	class Renderer
	{
	public:
		static GraphicsAPI getGraphicsAPI() { return graphicsAPI_opengl; }

	};
}