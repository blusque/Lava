#pragma once
#include <memory>

#include "Lava/Renderer/VertexArray.h"

#define OFFSET(x) (reinterpret_cast<const void*>(x))

namespace Lava
{
    
    class OpenGLVertexArray: public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        
        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const VertexBufferPtr& vbo) override;
        void SetIndexBuffer(const IndexBufferPtr& ibo) override;
    };
}
