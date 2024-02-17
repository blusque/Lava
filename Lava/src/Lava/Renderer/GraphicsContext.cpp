#include "lvpch.h"
#include "GraphicsContext.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Lava
{
    IGraphicsContext* GraphicsContextFactory::Create() const
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::API::OpenGL: return new OpenGLContext();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
}
