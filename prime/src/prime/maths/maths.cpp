
#include "pch.h"
#include "maths.h"

#include <glm/gtc/matrix_transform.hpp>

namespace prime::maths
{
	mat4 getTransform(const vec3& pos)
	{
		return glm::translate(glm::mat4(1.0f), pos);
	}
}