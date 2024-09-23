// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include <cstdint>
#include <filesystem>
#include <glm/glm.hpp>

namespace GLTK {
    class Shader {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        ~Shader();

        void Bind() const;
        static void Unbind();

        void SetBool(const char* name, bool value) const;
        void SetInt(const char* name, int value) const;
        void SetFloat(const char* name, float value) const;
        void SetVec2(const char* name, const glm::vec2& value) const;
        void SetVec2(const char* name, float x, float y) const;
        void SetVec3(const char* name, const glm::vec3& value) const;
        void SetVec3(const char* name, float x, float y, float z) const;
        void SetVec4(const char* name, const glm::vec4& value) const;
        void SetVec4(const char* name, float x, float y, float z, float w) const;
        void SetMat2(const char* name, const glm::mat2& mat) const;
        void SetMat3(const char* name, const glm::mat3& mat) const;
        void SetMat4(const char* name, const glm::mat4& mat) const;

    private:
        void CompileShaders(const char* vertexSource, const char* fragmentSource);
        static void CheckErrors(uint32_t handle, bool isProgram = false);
        uint32_t mProgramID = 0;
    };
}  // namespace GLTK