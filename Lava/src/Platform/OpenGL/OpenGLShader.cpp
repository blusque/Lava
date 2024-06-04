#include "lvpch.h"
#include "OpenGLShader.h"

#include <glad/gl.h>

namespace Lava
{
    OpenGLShader::OpenGLShader()
    {
        LV_PROFILE_FUNCTION();
        
        glUseProgram(m_RendererID);
    }

    OpenGLShader::~OpenGLShader()
    {
        LV_PROFILE_FUNCTION();
        
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
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniform1f(loc, value);
    }

    void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
    {
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniform3f(loc, v0, v1, v2);
    }

    void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniform4f(loc, v0, v1, v2, v3);
    }


    void OpenGLShader::SetUniform1i(const std::string& name, int value)
    {
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniform1i(loc, value);
    }

    void OpenGLShader::SetUniform1iv(const std::string& name, int len, const int* vec)
    {
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniform1iv(loc, len, vec);
    }

    void OpenGLShader::SetUniformMatrix4fv(const std::string& name, int count, unsigned char transpose, const float* ptr)
    {
        LV_PROFILE_FUNCTION();
        
        auto const loc = GetUniformLocation(name);
        glUniformMatrix4fv(loc, count, transpose, ptr);
    }

    void OpenGLShader::Compile(const ShaderProgram& program)
    {
        LV_PROFILE_FUNCTION();
        
        m_Name = program.ShaderName;
        auto const vertexShader = program.VertexShader.c_str();
        auto const fragmentShader = program.FragmentShader.c_str();
        m_RendererID = glCreateProgram();
        
        auto const vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vertexShader, nullptr);
        glCompileShader(vShader);

        GLint vertexCompiled;
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertexCompiled);
        if (vertexCompiled != GL_TRUE)
        {
            GLsizei logLength = 0;
            GLchar message[1024];
            glGetShaderInfoLog(vShader, 1024, &logLength, message);
            // Write the error to a log
            LV_CORE_ERROR("Vertex Shader Error: {0}", message);
        }
    
        auto const fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fragmentShader, nullptr);
        glCompileShader(fShader);

        GLint fragmentCompiled;
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragmentCompiled);
        if (fragmentCompiled != GL_TRUE)
        {
            GLsizei logLength = 0;
            GLchar message[1024];
            glGetShaderInfoLog(fShader, 1024, &logLength, message);
            // Write the error to a log
            LV_CORE_ERROR("Fragment Shader Error: {0}", message);
        }

        glAttachShader(m_RendererID, vShader);
        glAttachShader(m_RendererID, fShader);

        if (!program.GeometryShader.empty())
        {
            auto const geometryShader = program.GeometryShader.c_str();

            auto const gShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(gShader, 1, &geometryShader, nullptr);
            glCompileShader(gShader);

            GLint geometryCompiled;
            glGetShaderiv(gShader, GL_COMPILE_STATUS, &geometryCompiled);
            if (geometryCompiled != GL_TRUE)
            {
                GLsizei logLength = 0;
                GLchar message[1024];
                glGetShaderInfoLog(gShader, 1024, &logLength, message);
                LV_CORE_ERROR("Geometry Shader Error: {0}", message);
            }

            glAttachShader(m_RendererID, gShader);
        }
        
        glLinkProgram(m_RendererID);
        GLint programLinked;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &programLinked);
        if (programLinked != GL_TRUE)
        {
            GLsizei logLength = 0;
            GLchar message[1024];
            glGetProgramInfoLog(m_RendererID, 1024, &logLength, message);
            // Write the error to a log
            LV_CORE_ERROR("Link Error: {0}", message);
        }
    }

    int OpenGLShader::GetUniformLocation(const std::string& name)
    {
        LV_PROFILE_FUNCTION();
        
        if (m_UniformMap.find(name) == m_UniformMap.end())
        {
            m_UniformMap[name] = glGetUniformLocation(m_RendererID, name.c_str());
        }
        return m_UniformMap[name];
    }
}
