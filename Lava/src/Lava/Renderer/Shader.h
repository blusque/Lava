#pragma once

namespace Lava
{
    struct ShaderProgram
    {
        std::string VertexShader;
        std::string FragmentShader;
    };
    
    class LAVA_API Shader
    {
    public:
        using ptr = std::shared_ptr<Shader>;
        using uptr = std::unique_ptr<Shader>;
        
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual void SetUniform1f(const char* name, float value) const = 0;

        virtual void SetUniform3f(const char* name, float v0, float v1, float v2) const = 0;

        virtual void SetUniform1i(const char* name, int value) const = 0;

        virtual void SetUniform1iv(const char* name, int len, const int* vec) const = 0;

        virtual void SetUniformMatrix4fv(const char* name, int count, unsigned char transpose, const float* ptr) const = 0;

        virtual void Compile(const ShaderProgram& program) = 0;

        static Shader::ptr Create();

        static std::string ParserShaderProgram(const char* file);

    protected:
        unsigned int m_RendererID { 0 };
    };   
}
