#pragma once
#include "RenderAPI.h"
#include "VertexArray.h"

namespace Lava
{
    class Renderer
    {
    public:
        static void BeginScene();

        static void Submit(const VertexArrayPtr& vao);
        
        static void EndScene();

        static std::shared_ptr<RenderAPI> GetAPI();
    };
}

