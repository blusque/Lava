#pragma once

namespace Lava
{
    class IGraphicsContext
    {
    public:
        virtual ~IGraphicsContext() = default;

        virtual void Init(void* window) = 0;
        virtual void SwapBuffers(void* window) = 0;
    };

    using IGraphicsContextUPtr = std::unique_ptr<IGraphicsContext>;
    
    class FGraphicsContext
    {
    public:
        virtual ~FGraphicsContext() = default;
        
        virtual IGraphicsContext* [[nodiscard]] CreateGraphicsContext() = 0;    
    };

    using FGraphicsContextUPtr = std::unique_ptr<FGraphicsContext>;
}
