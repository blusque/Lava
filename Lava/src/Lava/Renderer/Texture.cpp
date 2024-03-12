#include "lvpch.h"
#include "Texture.h"

#include "Lava/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lava
{
    Ref<Texture> Texture::Create(const char* filename)
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return CreateRef<OpenGLTexture>(filename);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

    Ref<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return CreateRef<OpenGLTexture>(width, height);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
}
