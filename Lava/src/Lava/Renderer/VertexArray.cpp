#include "lvpch.h"
#include "VertexArray.h"
#include "RenderAPI.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace Lava
{
    void VertexArray::AddVertexBuffer(const VertexBuffer::ptr& vbo)
    {
        if (vbo)
        {
            LV_CORE_ASSERT(!vbo->GetLayout().empty(), "Vertex Buffer has no Layout!")
            vbo->Bind();
            m_VertexBuffers.push_back(vbo);
        }
    }

    void VertexArray::SetIndexBuffer(const IndexBuffer::ptr& ibo)
    {
        if (ibo)
        {
            ibo->Bind();
            m_IndexBuffer = ibo;
        }
    }

    VertexBuffer::ptr VertexArray::GetVertexBuffer(int index) const
    {
        if (m_VertexBuffers.empty() || m_VertexBuffers.size() < index)
            return nullptr;
        auto temp = m_VertexBuffers[index].lock();
        return temp;
    }

    IndexBuffer::ptr VertexArray::GetIndexBuffer() const
    {
        auto temp = m_IndexBuffer.lock();
        if (!temp)
            return nullptr;
        return temp;
    }

    VertexArray::ptr VertexArray::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None");
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }
        
        LV_CORE_ERROR("Wrong API type!");
        return nullptr;
    }

}
