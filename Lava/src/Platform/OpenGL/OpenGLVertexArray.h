﻿#pragma once
#include "Lava/Renderer/VertexArray.h"

namespace Lava
{
    
    class OpenGLVertexArray: public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        
        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const Ref<VertexBuffer>& vbo) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& ibo) override;
    };
}
