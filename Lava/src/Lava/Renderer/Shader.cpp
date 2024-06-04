#include "lvpch.h"
#include "Shader.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Lava
{
    Ref<Shader> Shader::Create()
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return CreateRef<OpenGLShader>();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

    ShaderProgram Shader::ParseShaderProgram(const std::string& file)
    {
        LV_PROFILE_FUNCTION();
        
        auto source = std::string();
        auto result = ShaderProgram();

        auto lastSlash = file.find_last_of("/\\");
        auto begin = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = file.rfind('.');
        auto count = lastDot == std::string::npos ? file.size() - begin : lastDot - begin;
        result.ShaderName = file.substr(begin, count);
        LV_CORE_INFO("Shader Name: {0}", result.ShaderName);
        
        if (auto fin = std::ifstream(file, std::ios::in, std::ios::binary))
        {
            fin.seekg(0, std::ios::end);
            source.resize(fin.tellg());
            fin.seekg(0, std::ios::beg);
            fin.read(source.data(), static_cast<std::streamsize>(source.size()));
            fin.close();
        }
        else
        {
            LV_CORE_WARN("Cannot open the shader file of {0}!", file);
        }

        auto const typeToken = std::string("#type");
        auto type = std::string();
        auto pos = source.find(typeToken);
        while (pos != std::string::npos)
        {
            auto const eol = source.find_first_of("\r\n", pos);
            LV_CORE_ASSERT(eol != std::string::npos, "Syntax Error!")
            auto const begin = pos + typeToken.size() + 1;
            type = source.substr(begin, eol - begin);
            LV_CORE_ASSERT(type == "vertex" || type == "geometry" || type == "fragment",
                "Type Error, should be 'vertex' or 'fragment', check whether you add extra space before them!")

            auto const nextLine = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLine);
            if (type == "vertex")
            {
                result.VertexShader = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
            }
            else if (type == "geometry")
            {
                result.GeometryShader = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
            }
            else if (type == "fragment")
            {
                result.FragmentShader = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
            }
        }
        
        return result;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        LV_PROFILE_FUNCTION();
        
        auto const name = shader->GetName();
        LV_CORE_ASSERT(m_Library.find(name) == m_Library.end(), "Repeated Shader Name!")
        m_Library[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& file)
    {
        LV_PROFILE_FUNCTION();
        
        auto const shader = Shader::Create();
        auto const program = Shader::ParseShaderProgram(file);
        shader->Compile(program);
        Add(shader);
    }

    void ShaderLibrary::Load(const std::string& name, const std::string& vertex, const std::string& fragment)
    {
        LV_PROFILE_FUNCTION();
        
        auto const shader = Shader::Create();
        auto const program = ShaderProgram{ name, vertex, fragment };
        shader->Compile(program);
        Add(shader);
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        LV_PROFILE_FUNCTION();
        
        LV_CORE_ASSERT(m_Library.find(name) != m_Library.end(), "No Valid Shader!")
        return m_Library[name];
    }

    Ref<Shader> ShaderLibrary::operator[](const std::string& name)
    {
        LV_PROFILE_FUNCTION();
        
        LV_CORE_ASSERT(m_Library.find(name) != m_Library.end(), "No Valid Shader!")
        return m_Library[name];
    }

    void ShaderLibrary::Remove(const std::string& name)
    {
        LV_PROFILE_FUNCTION();
        
        LV_CORE_ASSERT(m_Library.find(name) != m_Library.end(), "No Valid Shader!")
        m_Library.erase(name);
    }
}
