
#include "editor.h"

namespace prime
{
	void Editor::init()
	{
		renderer::RenderCommand::clearColor({ .2f, .2f, .2f, 1.0f });
		renderer::Renderer2D::init();
	}

	void Editor::shutdown()
	{
		renderer::Renderer2D::shutdown();
	}

	void Editor::update()
	{
		renderer::RenderCommand::clear();

		renderer::Renderer2D::begin();
		renderer::Renderer2D::drawSprite(scene::Transform(), { 0.0f, 0.0f, 1.0f, 1.0f });
		renderer::Renderer2D::end();
	}

	core::GameConfig Editor::GetConfig()
	{
		return core::GameConfig();
	}
}