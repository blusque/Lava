#pragma once
#include "Lava/Renderer/GraphicsContext.h"

namespace Lava
{
    class OpenGLContext: public IGraphicsContext
    {
    public:
        void Init(void* window) override;
        void SwapBuffers(void* window) override;
    };
    
    class OpenGLContextFactory: public FGraphicsContext
    {
    public:
        IGraphicsContext* [[nodiscard]] CreateGraphicsContext() override;
    };
}
