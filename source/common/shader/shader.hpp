#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{

    class ShaderProgram
    {

    private:
        // Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        ShaderProgram()
        {
            // TODO: (Req 1) Create A shader program
            program = glCreateProgram();
        }
        ~ShaderProgram()
        {
            // TODO: (Req 1) Delete a shader program
            glDeleteProgram(program);
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use()
        {
            glUseProgram(program);
        }

        GLuint getUniformLocation(const GLchar *name)
        {
            // TODO: (Req 1) Return the location of the uniform with the given name
            return glGetUniformLocation(program, name);
        }

        void set(const GLchar *uniform, GLfloat value)
        {
            // TODO: (Req 1) Send the given float value to the given uniform
            glUniform1f(getUniformLocation(uniform), value);
        }

        void set(const GLchar *uniform, GLuint value)
        {
            // TODO: (Req 1) Send the given unsigned integer value to the given uniform
            glUniform1ui(getUniformLocation(uniform), value);
        }

        void set(const GLchar *uniform, GLint value)
        {
            // TODO: (Req 1) Send the given integer value to the given uniform
            glUniform1i(getUniformLocation(uniform), value);
        }

        void set(const GLchar *uniform, glm::vec2 value)
        {
            // TODO: (Req 1) Send the given 2D vector value to the given uniform
            glUniform2fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const GLchar *uniform, glm::vec3 value)
        {
            // TODO: (Req 1) Send the given 3D vector value to the given uniform
            glUniform3fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const GLchar *uniform, glm::vec4 value)
        {
            // TODO: (Req 1) Send the given 4D vector value to the given uniform
            glUniform4fv(getUniformLocation(uniform), 1, glm::value_ptr(value));
        }

        void set(const GLchar *uniform, glm::mat4 matrix)
        {
            // TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(matrix));
        }

        // TODO: (Req 1) Delete the copy constructor and assignment operator.
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram &operator=(const ShaderProgram &) = delete;
        // Question: Why do we delete the copy constructor and assignment operator?

        // ~
        // * DONE: We don't need copy constructor and assignment operator because we are managing OpenGL resources (shader program) explicitly.
        // *      This prevents accidental copies of our ShaderProgram object.
        // *      Also, it prevents accidental modification of our ShaderProgram object.
        // ~ Singleton Pattern
    };

}

#endif