
#include "pch.h"
#include "scene.h"
#include "entity.h"
#include "components.h"
#include "prime/renderer/renderer2D.h"

namespace prime::scene
{
	Entity Scene::createEntity()
	{
		Entity entity(m_registry.create(), this);
		entity.addComponent<Transform>();

		return entity;
	}

	void Scene::destroyEntity(const Entity& entity)
	{
		m_registry.destroy(entity.GetHandle());
	}

	void Scene::render()
	{
		renderer::Renderer2D::begin();

		auto s_entities = m_registry.view<Transform, SpriteRenderer2D>();
		for (entt::entity s_entity : s_entities)
		{
			auto [s_entity_t, s_entity_s] = s_entities.get<Transform, SpriteRenderer2D>(s_entity);
			renderer::Renderer2D::drawSprite(s_entity_t, s_entity_s.color);
		}

		renderer::Renderer2D::end();
	}
}