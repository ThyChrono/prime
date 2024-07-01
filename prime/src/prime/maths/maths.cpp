
#include "pch.h"
#include "maths.h"
#include "prime/scene/components.h"

#include <glm/gtc/matrix_transform.hpp>

namespace prime::maths
{
	mat4 getTransform2D(const scene::Transform& transform)
	{
		return glm::translate(glm::mat4(1.0f), transform.position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { transform.scale.x, transform.scale.y, 1.0f });
	}
}