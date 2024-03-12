#pragma once

namespace Lava
{
    struct ShaderProgram
    {
        std::string ShaderName;
        std::string VertexShader;
        std::string FragmentShader;
    };
    
    class LAVA_API Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual std::string GetName() const = 0;
        
        virtual void SetUniform1f(const std::string& name, float value) = 0;

        virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;

        virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

        virtual void SetUniform1i(const std::string& name, int value) = 0;

        virtual void SetUniform1iv(const std::string& name, int len, const int* vec) = 0;

        virtual void SetUniformMatrix4fv(const std::string& name, int count, unsigned char transpose, const float* ptr) = 0;

        virtual void Compile(const ShaderProgram& program) = 0;

        static Ref<Shader> Create();

        static ShaderProgram ParseShaderProgram(const std::string& file);

    protected:
        unsigned int m_RendererID { 0 };
        std::string m_Name;
    };

    class LAVA_API ShaderLibrary
    {
    public:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;

        void Add(const Ref<Shader>& shader);
        
        void Load(const std::string& file);
        void Load(const std::string& name, const std::string& vertex, const std::string& fragment);

        Ref<Shader> Get(const std::string& name);
        Ref<Shader> operator[](const std::string& name);
        
        void Remove(const std::string& name);

        class iterator {
        public:
            iterator(const std::unordered_map<std::string, Ref<Shader>>::iterator& it) : it(it) {}
            iterator operator++() { return ++it; }
            auto& operator*() const { return *it; }
            bool operator!=(const iterator& other) const { return it != other.it; }
        private:
            std::unordered_map<std::string, Ref<Shader>>::iterator it;
        };
    
        iterator begin() { return {m_Library.begin()}; }
        iterator end() { return {m_Library.end()}; }

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Library;
    };
}
