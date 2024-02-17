#include "lvpch.h"
#include "OpenGLBuffer.h"

namespace Lava
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, unsigned size, BufferUseType utype)
    {
        m_Size = size;
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, UseTypeMap(utype));
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    
    [[nodiscard]] bool OpenGLVertexBuffer::BufferData(float* data, unsigned int size, BufferUseType utype) const   
    {
        if (size != m_Size)
        {
            return false;   
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, UseTypeMap(utype));
        return true;
    }
    
    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, unsigned int size, BufferUseType utype)
    {
        m_Size = size;
        m_Count = size / sizeof(unsigned int);
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, data, UseTypeMap(utype));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    [[nodiscard]] bool OpenGLIndexBuffer::BufferData(unsigned int* data, unsigned int size, BufferUseType utype) const
    {
        if (size != m_Size)
        {
            return false;
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, UseTypeMap(utype));
        return true;
    }
}

