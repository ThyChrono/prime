
#include "pch.h"
#include "maths.h"
#include "prime/scene/components.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace prime::maths
{
	mat4 getTransform(const scene::Transform& transform)
	{
		glm::mat4 rotation = glm::toMat4(glm::quat(transform.rotation));

		return glm::translate(glm::mat4(1.0f), transform.position)
			* rotation
			* glm::scale(glm::mat4(1.0f), { transform.scale.x, transform.scale.y, 1.0f });
	}
}