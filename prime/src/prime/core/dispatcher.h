#pragma once

#include "defines.h"

#include <entt/entt.hpp>

namespace prime::core
{
	class Dispatcher
	{
	private:
		PINLINE static entt::dispatcher m_dispatcher;

	public:
		static entt::dispatcher& get() { return m_dispatcher; }

		static void update()
		{
			m_dispatcher.update();
		}

		static void clear()
		{
			m_dispatcher.clear();
		}
	};
}
