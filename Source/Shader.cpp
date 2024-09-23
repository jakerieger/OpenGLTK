// Author: Jake Rieger
// Created: 9/23/2024.
//

#include "Shader.h"
#include "Panic.h"
#include "IO.h"

#include <glad/glad.h>

namespace GLTK {
    Shader::Shader(const char* vertexSource, const char* fragmentSource) {
        CompileShaders(vertexSource, fragmentSource);
    }

    Shader::Shader(const Path& vertexPath, const Path& fragmentPath) {
        if (!std::filesystem::exists(vertexPath) || !std::filesystem::exists(fragmentPath)) {
            const auto fmt = std::format("Path does not exist: {}", vertexPath.string());
            Panic(fmt.c_str());
        }

        const auto vertexSource = IO::Read(vertexPath).value_or("");
        if (vertexSource.empty())
            Panic("Could not read vertex shader");
        const auto fragmentSource = IO::Read(fragmentPath).value_or("");
        if (fragmentSource.empty())
            Panic("Could not read fragment shader");

        CompileShaders(vertexSource.c_str(), fragmentSource.c_str());
    }

    Shader::~Shader() {
        glDeleteProgram(mProgramID);
    }

    void Shader::Bind() const {
        glUseProgram(mProgramID);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::CompileShaders(const char* vertexSource, const char* fragmentSource) {
        const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);
        CheckErrors(vertexShader);

        const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);
        CheckErrors(fragmentShader);

        mProgramID = glCreateProgram();
        glAttachShader(mProgramID, vertexShader);
        glAttachShader(mProgramID, fragmentShader);
        glLinkProgram(mProgramID);
        CheckErrors(mProgramID, true);
        glValidateProgram(mProgramID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::CheckErrors(uint32_t handle, bool isProgram) {
        int success;
        char infoLog[1024];

        if (isProgram) {
            glGetProgramiv(handle, GL_LINK_STATUS, &success);

            if (!success) {
                glGetProgramInfoLog(handle, 1024, nullptr, infoLog);
                Panic(infoLog);
            }
        } else {
            glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(handle, 1024, nullptr, infoLog);
                Panic(infoLog);
            }
        }
    }

    void Shader::SetBool(const char* name, bool value) const {
        glUniform1i(glGetUniformLocation(mProgramID, name), static_cast<int>(value));
    }

    void Shader::SetInt(const char* name, int value) const {
        glUniform1i(glGetUniformLocation(mProgramID, name), value);
    }

    void Shader::SetFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(mProgramID, name), value);
    }

    void Shader::SetVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(mProgramID, name), 1, &value[0]);
    }

    void Shader::SetVec2(const char* name, float x, float y) const {
        glUniform2f(glGetUniformLocation(mProgramID, name), x, y);
    }

    void Shader::SetVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(mProgramID, name), 1, &value[0]);
    }

    void Shader::SetVec3(const char* name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(mProgramID, name), x, y, z);
    }

    void Shader::SetVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(mProgramID, name), 1, &value[0]);
    }

    void Shader::SetVec4(const char* name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(mProgramID, name), x, y, z, w);
    }

    void Shader::SetMat2(const char* name, const glm::mat2& mat) const {
        glUniformMatrix2fv(glGetUniformLocation(mProgramID, name), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const char* name, const glm::mat3& mat) const {
        glUniformMatrix3fv(glGetUniformLocation(mProgramID, name), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const char* name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(mProgramID, name), 1, GL_FALSE, &mat[0][0]);
    }

}  // namespace GLTK