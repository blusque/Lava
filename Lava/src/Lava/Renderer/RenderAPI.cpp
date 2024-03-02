#include "lvpch.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Lava
{
    RenderAPI::Platform RenderAPI::GetPlatform()
    {
        static Platform s_API = Platform::OpenGL;
        return s_API;
    }

    Ref<RenderAPI> RenderAPI::GetAPI()
    {
        static std::shared_ptr<RenderAPI> api = nullptr;
        if (api)
        {
            return api;
        }
        else
        {
            switch (GetPlatform())
            {
            case Platform::None: LV_CORE_ERROR("A render API should be specific, now is None"); break;
            case Platform::OpenGL: api.reset(OpenGLRenderer::GetAPI()); break;
            default: LV_CORE_ERROR("Wrong API type!");
            }
        
            return api;
        }
    }
}
