#include "lvpch.h"
#include "GraphicsContext.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Lava
{
    IGraphicsContext* GraphicsContextFactory::Create() const
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return new OpenGLContext();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
}
