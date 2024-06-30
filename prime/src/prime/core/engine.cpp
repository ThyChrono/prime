
#include "pch.h"
#include "engine.h"
#include "dispatcher.h"
#include "events.h"
#include "prime/renderer/render_command.h"

namespace prime::core
{
	static b8 s_running = false;
	Engine::Data Engine::s_data;

	static void OnWidowClose(const WindowCloseEvent& e)
	{
		s_running = false;
	}

	void Engine::run(Game* game)
	{
		Logger::init();
		renderer::createDummyContext();
		GameConfig gc = game->GetConfig();

		// window
		WindowConfig wc;
		wc.title = gc.title;
		wc.width = gc.width;
		wc.height = gc.height;
		s_data.window.init(wc);

		// dispatcher
		Dispatcher::get().sink<WindowCloseEvent>().connect<OnWidowClose>();

		// renderer
		renderer::RenderCommand::init();

		game->init();
		s_running = true;

		while (s_running)
		{
			pollEvents();
			Dispatcher::update();

			game->update();
			s_data.window.update();
		}

		game->shutdown();
		Dispatcher::clear();
		s_data.window.shutdown();
		Logger::shutdown();
	}
}