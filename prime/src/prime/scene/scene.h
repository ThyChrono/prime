#pragma once

#include <entt/entt.hpp>

namespace prime::scene {

	class Entity;

	class Scene
	{
	private:
		friend class Entity;

		entt::registry m_registry;

	public:
		Entity createEntity();
		void destroyEntity(const Entity& entity);

		void render();
	};
}
