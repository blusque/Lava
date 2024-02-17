#include "lvpch.h"
#include "OpenGLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/gl.h>

namespace Lava
{
    Shader::Shader(const char* vShaderFile, const char* fShaderFile)
    {
        auto const vs = ParserShader(vShaderFile);
        auto const fs = ParserShader(fShaderFile);
        m_Renderer = CreateShaderProgram(vs.c_str(), fs.c_str());
        glUseProgram(m_Renderer);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_Renderer);
        glUseProgram(0);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_Renderer);
    }

    void Shader::SetUniform1f(const char* name, float value) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1f(loc, value);
    }

    void Shader::SetUniform3f(const char* name, float v0, float v1, float v2) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform3f(loc, v0, v1, v2);
    }

    void Shader::SetUniform1i(const char* name, int value) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1i(loc, value);
    }

    void Shader::SetUniform1iv(const char* name, int len, const int* vec) const
    {
        auto const loc = GetUniformLocation(name);
        glUniform1iv(loc, len, vec);
    }

    void Shader::SetUniformMatrix4fv(const char* name, int count, unsigned char transpose, const float* ptr) const
    {
        auto const loc = GetUniformLocation(name);
        glUniformMatrix4fv(loc, count, transpose, ptr);
    }

    std::string Shader::ParserShader(const char* file)
    {
        auto is = std::ifstream(file);
        auto ss = std::stringstream();
        auto line = std::string();
        if (!is.is_open())
        {
            std::cerr << "File: " << file << " is not opened!\n";
            return ss.str();
        }
        while (getline(is, line))
        {
            ss << line << '\n';
        }
        return ss.str();
    }

    unsigned Shader::CreateShaderProgram(const char* vertexShader, const char* fragmentShader)
    {
        auto const shader = glCreateProgram();
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

        glAttachShader(shader, vShader);
        glAttachShader(shader, fShader);
        glLinkProgram(shader);
        GLint program_linked;
        glGetProgramiv(shader, GL_LINK_STATUS, &program_linked);
        if (fragment_compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(shader, 1024, &log_length, message);
            // Write the error to a log
            printf("Link Error: %s", message);
        }
        return shader;
    }

    int Shader::GetUniformLocation(const char* name) const
    {
        return glGetUniformLocation(m_Renderer, name);
    }
}
