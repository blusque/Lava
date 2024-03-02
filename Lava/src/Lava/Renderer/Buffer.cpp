#include "lvpch.h"
#include "Buffer.h"
#include "RenderAPI.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Lava
{
    VertexBuffer::VertexBuffer()
        : m_Layout(new BufferLayout)
    {
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size, BufferUseType utype)
    {
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return std::make_shared<OpenGLVertexBuffer>(data, size, utype);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }
    
    Ref<IndexBuffer> IndexBuffer::Create(unsigned* data, uint32_t size, BufferUseType utype)
    {
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return std::make_shared<OpenGLIndexBuffer>(data, size, utype);
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

}
