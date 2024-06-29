
#include "pch.h"
#include "engine.h"
#include "dispatcher.h"
#include "events.h"

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
		GameConfig gc = game->GetConfig();

		// window
		WindowConfig wc;
		wc.title = gc.title;
		wc.width = gc.width;
		wc.height = gc.height;
		s_data.window.init(wc);

		// dispatcher
		Dispatcher::get().sink<WindowCloseEvent>().connect<OnWidowClose>();

		game->init();
		s_running = true;

		while (s_running)
		{
			pollEvents();
			Dispatcher::update();
			game->update();
		}

		game->shutdown();
		Dispatcher::clear();
		s_data.window.shutdown();
	}
}