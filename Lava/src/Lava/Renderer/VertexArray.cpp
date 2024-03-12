#include "lvpch.h"
#include "VertexArray.h"
#include "RenderAPI.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace Lava
{
    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vbo)
    {
        LV_PROFILE_FUNCTION();
        
        if (vbo)
        {
            LV_CORE_ASSERT(!vbo->GetLayout().empty(), "Vertex Buffer has no Layout!")
            vbo->Bind();
            m_VertexBuffers.push_back(vbo);
        }
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ibo)
    {
        LV_PROFILE_FUNCTION();
        
        if (ibo)
        {
            ibo->Bind();
            m_IndexBuffer = ibo;
        }
    }

    Ref<VertexBuffer> VertexArray::GetVertexBuffer(int index) const
    {
        if (m_VertexBuffers.empty() || m_VertexBuffers.size() < index)
            return nullptr;
        return m_VertexBuffers[index];
    }

    Ref<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        if (!m_IndexBuffer)
            return nullptr;
        return m_IndexBuffer;
    }

    Ref<VertexArray> VertexArray::Create()
    {
        LV_PROFILE_FUNCTION();
        
        switch (RenderAPI::GetPlatform())
        {
        case RenderAPI::Platform::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::Platform::OpenGL: return CreateRef<OpenGLVertexArray>();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

}
