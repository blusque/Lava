#pragma once
#include <memory>
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
        
        void SetUniform1f(const char* name, float value) const override;

        void SetUniform3f(const char* name, float v0, float v1, float v2) const override;

        void SetUniform1i(const char* name, int value) const override;

        void SetUniform1iv(const char* name, int len, const int* vec) const override;

        void SetUniformMatrix4fv(const char* name, int count, unsigned char transpose, const float* ptr) const override;
        
        void Compile(const ShaderProgram& program) override;
        
    private:
        int GetUniformLocation(const char* name) const;
    };

    using ShaderPtr = std::shared_ptr<Shader>;
    using ShaderUPtr = std::unique_ptr<Shader>;
}

