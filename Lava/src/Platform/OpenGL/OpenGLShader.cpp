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

    std::string OpenGLShader::GetName() const
    {
        return m_Name;
    }


    void OpenGLShader::SetUniform1f(const std::string& name, float value)
    {
        auto const loc = GetUniformLocation(name);
        glUniform1f(loc, value);
    }

    void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
    {
        auto const loc = GetUniformLocation(name);
        glUniform3f(loc, v0, v1, v2);
    }

    void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        auto const loc = GetUniformLocation(name);
        glUniform4f(loc, v0, v1, v2, v3);
    }


    void OpenGLShader::SetUniform1i(const std::string& name, int value)
    {
        auto const loc = GetUniformLocation(name);
        glUniform1i(loc, value);
    }

    void OpenGLShader::SetUniform1iv(const std::string& name, int len, const int* vec)
    {
        auto const loc = GetUniformLocation(name);
        glUniform1iv(loc, len, vec);
    }

    void OpenGLShader::SetUniformMatrix4fv(const std::string& name, int count, unsigned char transpose, const float* ptr)
    {
        auto const loc = GetUniformLocation(name);
        glUniformMatrix4fv(loc, count, transpose, ptr);
    }

    void OpenGLShader::Compile(const ShaderProgram& program)
    {
        m_Name = program.ShaderName;
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

    int OpenGLShader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformMap.find(name) == m_UniformMap.end())
        {
            m_UniformMap[name] = glGetUniformLocation(m_RendererID, name.c_str());
        }
        return m_UniformMap[name];
    }
}
