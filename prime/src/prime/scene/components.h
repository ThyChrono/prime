#pragma once

#include "prime/maths/maths.h"

namespace prime::scene
{
	class Transform
	{
	public:
		maths::vec3 position = maths::vec3(0.0f);
		maths::vec3 scale = maths::vec3(1.0f);
		maths::vec3 rotation = maths::vec3(0.0f);

	public:
		Transform() = default;

		Transform(const maths::vec3& pos) : position(pos) {}
		Transform(const maths::vec3& pos, const maths::vec3& scale) 
			: position(pos), scale(scale) {}
	};
}
