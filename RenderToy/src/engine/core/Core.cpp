#include "Core.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        spdlog::error("[OpenGL Error] ({}", error, ")");
        spdlog::error(function + (std::string)" " + file + ":" + std::to_string(line));
        return false;
    }
    return true;
}

namespace core
{
    glm::mat4 core::GetRodrigue(glm::vec4 axis, float angle)
    {
        glm::mat3 part1 = glm::cos(glm::radians(angle)) * glm::mat3(1.0f);
        glm::mat3 nnt = glm::mat3(
            axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
            axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
            axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
        );
        glm::mat3 part2 = (1 - glm::cos(glm::radians(angle))) * nnt;
        glm::mat3 part3 = glm::mat3(
            0.0f, -axis.z, axis.y,
            axis.z, 0.0f, -axis.x,
            -axis.y, axis.x, 0.0f
        );
        part3 = glm::sin(glm::radians(angle)) * part3;
        glm::mat3 rodrigueMat3 = part1 + part2 + part3;
        glm::mat4 rodrigue;
        rodrigue[0] = glm::vec4(rodrigueMat3[0], 0.0f);
        rodrigue[1] = glm::vec4(rodrigueMat3[1], 0.0f);
        rodrigue[2] = glm::vec4(rodrigueMat3[2], 0.0f);
        rodrigue[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return rodrigue;
    }
}