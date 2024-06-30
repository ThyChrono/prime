#pragma once

#include "prime/core/defines.h"

#include <glm/glm.hpp>

namespace prime::maths
{
    /** @brief a vec2 */
    using vec2 = glm::vec2;

    /** @brief a vec3 */
    using vec3 = glm::vec3;

    /** @brief a vec4 */
    using vec4 = glm::vec4;

    /** @brief a mat4 */
    using mat4 = glm::mat4;

    mat4 getTransform(const maths::vec3& pos, const maths::vec2& scale, f32 rotation);
}
