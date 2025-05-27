//
// Created by user on 5/16/25.
//

#ifndef CONSERVATION_UTILITIES_SHADER_H
#define CONSERVATION_UTILITIES_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <string_view>

namespace csv
{
    class Shader
    {
    public:
        [[nodiscard]] static Shader load(const std::filesystem::path& vertexShaderFile,
                                         const std::filesystem::path& fragmentShaderFile);

        explicit Shader(GLuint program);

        Shader(const Shader& other) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other) noexcept;

        [[nodiscard]] GLuint program() const;

        [[nodiscard]] GLint getUniformLocation(std::string_view name) const;

        template<typename... Args>
        void setUniform(std::string_view name, Args... args) const;

        void use() const;

    private:
        GLuint m_program;

        static void setUniform(GLint location, GLint value);
        static void setUniform(GLint location, GLfloat value);
        static void setUniform(GLint location, GLuint value);
        static void setUniform(GLint location, bool value);
        static void setUniform(GLint location, const glm::ivec1& value);
        static void setUniform(GLint location, const glm::fvec1& value);
        static void setUniform(GLint location, const glm::uvec1& value);
        static void setUniform(GLint location, const glm::bvec1& value);
        static void setUniform(GLint location, const glm::dvec1& value);

        static void setUniform(GLint location, GLint x, GLint y);
        static void setUniform(GLint location, GLfloat x, GLfloat y);
        static void setUniform(GLint location, GLuint x, GLuint y);
        static void setUniform(GLint location, bool x, bool y);
        static void setUniform(GLint location, const glm::ivec2& value);
        static void setUniform(GLint location, const glm::fvec2& value);
        static void setUniform(GLint location, const glm::uvec2& value);
        static void setUniform(GLint location, const glm::bvec2& value);
        static void setUniform(GLint location, const glm::dvec2& value);
        static void setUniform(GLint location, const glm::fmat2x2& value);

        static void setUniform(GLint location, GLint x, GLint y, GLint z);
        static void setUniform(GLint location, GLfloat x, GLfloat y, GLfloat z);
        static void setUniform(GLint location, GLuint x, GLuint y, GLuint z);
        static void setUniform(GLint location, bool x, bool y, bool z);
        static void setUniform(GLint location, const glm::ivec3& value);
        static void setUniform(GLint location, const glm::fvec3& value);
        static void setUniform(GLint location, const glm::uvec3& value);
        static void setUniform(GLint location, const glm::bvec3& value);
        static void setUniform(GLint location, const glm::dvec3& value);
        static void setUniform(GLint location, const glm::fmat3x2& value);
        static void setUniform(GLint location, const glm::fmat3x3& value);

        static void setUniform(GLint location, GLint x, GLint y, GLint z, GLint w);
        static void setUniform(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        static void setUniform(GLint location, GLuint x, GLuint y, GLuint z, GLuint w);
        static void setUniform(GLint location, bool x, bool y, bool z, bool w);
        static void setUniform(GLint location, const glm::ivec4& value);
        static void setUniform(GLint location, const glm::fvec4& value);
        static void setUniform(GLint location, const glm::uvec4& value);
        static void setUniform(GLint location, const glm::bvec4& value);
        static void setUniform(GLint location, const glm::dvec4& value);
        static void setUniform(GLint location, const glm::fmat2x4& value);
        static void setUniform(GLint location, const glm::fmat3x4& value);
        static void setUniform(GLint location, const glm::fmat4x4& value);
    };

    template<typename... Args>
    void Shader::setUniform(const std::string_view name, Args... args) const
    {
        setUniform(getUniformLocation(name), std::forward<Args>(args)...);
    }
} // lgl

#endif //CONSERVATION_UTILITIES_SHADER_H
