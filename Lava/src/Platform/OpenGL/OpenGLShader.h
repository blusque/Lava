#pragma once
#include <memory>
#include <string>

namespace Lava
{
    class Shader
    {
    public:
        Shader(const char* vShaderFile, const char* fShaderFile);
        ~Shader();

        void Bind() const;
        
        void SetUniform1f(const char* name, float value) const;

        void SetUniform3f(const char* name, float v0, float v1, float v2) const;

        void SetUniform1i(const char* name, int value) const;

        void SetUniform1iv(const char* name, int len, const int* vec) const;

        void SetUniformMatrix4fv(const char* name, int count, unsigned char transpose, const float* ptr) const;

    private:
        static std::string ParserShader(const char* file);
        static unsigned int CreateShaderProgram(const char* vertexShader, const char* fragmentShader);

        int GetUniformLocation(const char* name) const;
        
    private:
        unsigned int m_Renderer { 0 };
    };

    using ShaderPtr = std::shared_ptr<Shader>;
    using ShaderUPtr = std::unique_ptr<Shader>;
}

