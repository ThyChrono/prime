#pragma once

#include "prime/prime.h"

namespace prime {

	class Editor : public core::Game
	{
	private:
		Ref<scene::Scene> m_scene;

	public:
		void init() override;
		void shutdown() override;

		void update() override;
		core::GameConfig GetConfig() override;
	};
}
