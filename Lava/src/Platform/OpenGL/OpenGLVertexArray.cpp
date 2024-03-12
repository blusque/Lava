#include "lvpch.h"
#include "OpenGLVertexArray.h"

#include <glad/gl.h>

#include "OpenGLBuffer.h"

namespace Lava
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        LV_PROFILE_FUNCTION();
        
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteVertexArrays(1, &m_RendererID);
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vbo)
    {
        LV_PROFILE_FUNCTION();
        
        VertexArray::AddVertexBuffer(vbo);

        glBindVertexArray(m_RendererID);
        auto index = 0;
        auto offset = 0;
        for (auto&& layout : vbo->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, layout.Count, DataTypeMap(layout.Type),
                layout.Normalized ? GL_TRUE : GL_FALSE, vbo->GetStride(), OFFSET(offset));
            offset += layout.Count * static_cast<int>(layout.Size);
            index++;
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ibo)
    {
        LV_PROFILE_FUNCTION();
        
        VertexArray::SetIndexBuffer(ibo);
    }
}
