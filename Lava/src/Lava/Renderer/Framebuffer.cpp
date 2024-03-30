#include "lvpch.h"
#include "Framebuffer.h"

#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Lava
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferProps& props)
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return CreateRef<OpenGLFramebuffer>(props);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
}
