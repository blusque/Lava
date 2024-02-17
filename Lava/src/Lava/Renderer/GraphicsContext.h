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
    
    class GraphicsContextFactory
    {
    public:
        virtual ~GraphicsContextFactory() = default;

        static GraphicsContextFactory& GetFactory()
        {
            static GraphicsContextFactory factory;
            return factory;
        }
        
        IGraphicsContext* [[nodiscard]] Create() const;    
    };
}
