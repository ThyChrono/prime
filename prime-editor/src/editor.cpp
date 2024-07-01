
#include "editor.h"

namespace prime
{
	void Editor::init()
	{
		renderer::RenderCommand::clearColor({ .2f, .2f, .2f, 1.0f });
		renderer::Renderer2D::init();

		m_scene = createRef<scene::Scene>();
		scene::Entity entity = m_scene->createEntity();
		entity.addComponent<scene::SpriteRenderer2D>();
	}

	void Editor::shutdown()
	{
		renderer::Renderer2D::shutdown();
	}

	void Editor::update()
	{
		renderer::RenderCommand::clear();
		m_scene->render();
	}

	core::GameConfig Editor::GetConfig()
	{
		return core::GameConfig();
	}
}