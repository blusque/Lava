#pragma once
#include "Buffer.h"

namespace Lava
{
    class VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const VertexBufferPtr& vbo);
        virtual void SetIndexBuffer(const IndexBufferPtr& ibo);

        [[nodiscard]] virtual VertexBufferPtr GetVertexBuffer(int index) const;
        [[nodiscard]] virtual IndexBufferPtr GetIndexBuffer() const;

        static VertexArray* Create();

    protected:
        unsigned int m_RendererID;
        std::vector<std::weak_ptr<VertexBuffer>> m_VertexBuffers;
        std::weak_ptr<IndexBuffer> m_IndexBuffer;
    };

    using VertexArrayPtr = std::shared_ptr<VertexArray>;
    using VertexArrayUPtr = std::unique_ptr<VertexArray>;
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
