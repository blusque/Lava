#pragma once
#include "Buffer.h"

namespace Lava
{
    class LAVA_API VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vbo);
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& ibo);

        [[nodiscard]] virtual Ref<VertexBuffer> GetVertexBuffer(int index) const;
        [[nodiscard]] virtual Ref<IndexBuffer> GetIndexBuffer() const;

        static Ref<VertexArray> Create();

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
