#include "lvpch.h"
#include "OpenGLBuffer.h"

namespace Lava
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, unsigned size, BufferUseType utype)
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
    
    [[nodiscard]] bool OpenGLVertexBuffer::BufferData(float* data, unsigned int size, BufferUseType utype) const   
    {
        LV_PROFILE_FUNCTION();
        
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
        LV_PROFILE_FUNCTION();
        
        m_Size = size;
        m_Count = size / sizeof(unsigned int);
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

    [[nodiscard]] bool OpenGLIndexBuffer::BufferData(unsigned int* data, unsigned int size, BufferUseType utype) const
    {
        LV_PROFILE_FUNCTION();
        
        if (size != m_Size)
        {
            return false;
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, UseTypeMap(utype));
        return true;
    }
}

