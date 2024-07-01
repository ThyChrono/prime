#pragma once

#include "scene.h"
#include "prime/core/assert.h"

namespace prime::scene
{
	class Entity
	{
	private:
		entt::entity m_handle{ entt::null };
		Scene* m_scene = nullptr;

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene)
			: m_handle(handle), m_scene(scene) {}

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			PASSERT_MSG(!hasComponent<T>(), "Entity already has component!");
			T& component = m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& addOrReplaceComponent(Args&&... args)
		{
			T& component = m_scene->m_registry.emplace_or_replace<T>(m_handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& getComponent()
		{
			PASSERT_MSG(hasComponent<T>(), "Entity does not have component!");
			return m_scene->m_registry.get<T>(m_handle);
		}

		template<typename T>
		bool hasComponent()
		{
			return m_scene->m_registry.has<T>(m_handle);
		}

		template<typename T>
		void removeComponent()
		{
			PASSERT_MSG(hasComponent<T>(), "Entity does not have component!");
			m_scene->m_registry.remove<T>(m_handle);
		}

		entt::entity GetHandle() const { return m_handle; }

		operator bool() const { return m_handle != entt::null; }
		operator entt::entity() const { return m_handle; }
		operator uint32_t() const { return (uint32_t)m_handle; }

		bool operator==(const Entity& other) const
		{
			return m_handle == other.m_handle && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	};
}