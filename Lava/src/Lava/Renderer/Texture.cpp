#include "lvpch.h"
#include "Texture.h"

#include "Lava/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lava
{
    Ref<Texture> Texture::Create(const char* filename)
    {
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return std::make_shared<OpenGLTexture>(filename);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

}
