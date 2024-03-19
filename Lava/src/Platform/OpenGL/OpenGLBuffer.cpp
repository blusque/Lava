#include "lvpch.h"
#include "OpenGLBuffer.h"

namespace Lava
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const float* data, unsigned size, BufferUseType utype)
    {
        LV_PROFILE_FUNCTION();
        
        m_Size = size;
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, UseTypeMap(utype));
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::BufferData(const void* data, unsigned size) const
    {
        VertexBuffer::BufferData(data, size);

        LV_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
    
    OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int size, BufferUseType utype)
    {
        LV_PROFILE_FUNCTION();
        
        m_Size = size;
        m_Count = size / sizeof(uint32_t);
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, data, UseTypeMap(utype));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::BufferData(const void* data, unsigned size) const
    {
        IndexBuffer::BufferData(data, size);

        LV_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    }
}

