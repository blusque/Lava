#include "lvpch.h"
#include "Shader.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Lava
{
    Shader::ptr Shader::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

    std::string Shader::ParserShaderProgram(const char* file)
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
}
