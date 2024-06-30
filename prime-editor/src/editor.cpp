
#include "editor.h"

namespace prime
{
	void Editor::init()
	{
		renderer::RenderCommand::clearColor({ .2f, .2f, .2f, 1.0f });
	}

	void Editor::shutdown()
	{

	}

	void Editor::update()
	{
		renderer::RenderCommand::clear();
	}

	core::GameConfig Editor::GetConfig()
	{
		return core::GameConfig();
	}
}