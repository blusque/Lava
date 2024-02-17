﻿#include "lvpch.h"
#include "Buffer.h"
#include "RenderAPI.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Lava
{
    VertexBuffer::VertexBuffer()
        : m_Layout(new BufferLayout)
    {
    }

    VertexBuffer* VertexBuffer::Create(float* data, uint32_t size, BufferUseType utype)
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(data, size, utype);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
    
    IndexBuffer* IndexBuffer::Create(unsigned* data, uint32_t size, BufferUseType utype)
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(data, size, utype);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

}