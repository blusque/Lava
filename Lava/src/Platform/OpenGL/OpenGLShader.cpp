#include "lvpch.h"
#include "OpenGLShader.h"

#include <glad/gl.h>

namespace Lava
{
    OpenGLShader::OpenGLShader()
    {
        glUseProgram(m_RendererID);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
        glUseProgram(0);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }


    void OpenGLShader::SetUniform1f(const char* name, float value) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1f(loc, value);
    }

    void OpenGLShader::SetUniform3f(const char* name, float v0, float v1, float v2) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform3f(loc, v0, v1, v2);
    }

    void OpenGLShader::SetUniform1i(const char* name, int value) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1i(loc, value);
    }

    void OpenGLShader::SetUniform1iv(const char* name, int len, const int* vec) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1iv(loc, len, vec);
    }

    void OpenGLShader::SetUniformMatrix4fv(const char* name, int count, unsigned char transpose, const float* ptr) const
    {
        auto const loc = GetUniformLocation(name);
        glUniformMatrix4fv(loc, count, transpose, ptr);
    }

    void OpenGLShader::Compile(const ShaderProgram& program)
    {
        auto const vertexShader = program.VertexShader.c_str();
        auto const fragmentShader = program.FragmentShader.c_str();
        m_RendererID = glCreateProgram();
        auto const vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vertexShader, nullptr);
        glCompileShader(vShader);

        GLint vertex_compiled;
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertex_compiled);
        if (vertex_compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(vShader, 1024, &log_length, message);
            // Write the error to a log
            printf("Vertex Shader Error: %s", message);
        }
    
        auto const fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fragmentShader, nullptr);
        glCompileShader(fShader);

        GLint fragment_compiled;
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragment_compiled);
        if (fragment_compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(fShader, 1024, &log_length, message);
            // Write the error to a log
            printf("Fragment Shader Error: %s", message);
        }

        glAttachShader(m_RendererID, vShader);
        glAttachShader(m_RendererID, fShader);
        glLinkProgram(m_RendererID);
        GLint program_linked;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &program_linked);
        if (fragment_compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(m_RendererID, 1024, &log_length, message);
            // Write the error to a log
            printf("Link Error: %s", message);
        }
    }

    int OpenGLShader::GetUniformLocation(const char* name) const
    {
        return glGetUniformLocation(m_RendererID, name);
    }
}
