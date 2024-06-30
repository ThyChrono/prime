
#include "pch.h"
#include "maths.h"

#include <glm/gtc/matrix_transform.hpp>

namespace prime::maths
{
	mat4 getTransform(const maths::vec3& pos, const maths::vec2& scale, f32 rotation)
	{
		return glm::translate(glm::mat4(1.0f), pos)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
	}
}