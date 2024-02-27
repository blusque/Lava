#pragma once
#include "Buffer.h"

namespace Lava
{
    class LAVA_API VertexArray
    {
    public:
        using ptr = std::shared_ptr<VertexArray>;
        using uptr = std::unique_ptr<VertexArray>;
        
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const VertexBuffer::ptr& vbo);
        virtual void SetIndexBuffer(const IndexBuffer::ptr& ibo);

        [[nodiscard]] virtual VertexBuffer::ptr GetVertexBuffer(int index) const;
        [[nodiscard]] virtual IndexBuffer::ptr GetIndexBuffer() const;

        static VertexArray::ptr Create();

    protected:
        unsigned int m_RendererID;
        std::vector<std::weak_ptr<VertexBuffer>> m_VertexBuffers;
        std::weak_ptr<IndexBuffer> m_IndexBuffer;
    };
    
    // class VertexArrayFactory
    // {
    // public:
    //     static VertexArrayFactory& GetFactory()
    //     {
    //         static VertexArrayFactory factory;
    //         return factory;
    //     }
    //
    //     static VertexArray* Create();
    // };
}
