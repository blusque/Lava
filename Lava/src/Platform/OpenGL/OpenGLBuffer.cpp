#include "lvpch.h"
#include "OpenGLBuffer.h"

namespace Lava
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned size, BufferUseType utype)
    {
        LV_PROFILE_FUNCTION();
        
        m_Size = size;
        glCreateBuffers(1, &m_RendererID);
        // glNamedBufferData(m_RendererID, size, data, UseTypeMap(utype));
        glNamedBufferStorage(m_RendererID, size, data, GL_DYNAMIC_STORAGE_BIT);
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
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
        glNamedBufferSubData(m_RendererID, 0, size, data);
    }
    
    OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int size, BufferUseType utype)
    {
        LV_PROFILE_FUNCTION();
        
        m_Size = size;
        m_Count = size / sizeof(uint32_t);
        glCreateBuffers(1, &m_RendererID);
        // glNamedBufferData(m_RendererID, m_Size, data, UseTypeMap(utype));
        glNamedBufferStorage(m_RendererID, m_Size, data, GL_DYNAMIC_STORAGE_BIT);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
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
        glNamedBufferSubData(m_RendererID, 0, size, data);
    }
}

