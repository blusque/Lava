#pragma once
#include <string>

#include "Lava/Renderer/Shader.h"

namespace Lava
{
    class OpenGLShader: public Shader
    {
    public:
        OpenGLShader();
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        std::string GetName() const override;
        
        void SetUniform1f(const std::string& name, float value) override;

        void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;

        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;

        void SetUniform1i(const std::string& name, int value) override;

        void SetUniform1iv(const std::string& name, int len, const int* vec) override;

        void SetUniformMatrix4fv(const std::string& name, int count, unsigned char transpose, const float* ptr) override;
        
        void Compile(const ShaderProgram& program) override;
        
    private:
        int GetUniformLocation(const std::string& name);

    private:
        std::unordered_map<std::string, int> m_UniformMap;
    };
}

