#pragma once
#include <glad/gl.h>
#include "Lava/Renderer/Buffer.h"

namespace Lava
{
    inline GLenum UseTypeMap(BufferUseType utype)
    {
        switch (utype)
        {
        case BufferUseType::STATIC: return GL_STATIC_DRAW;
        case BufferUseType::DYNAMIC: return GL_DYNAMIC_DRAW;
        case BufferUseType::STREAM: return GL_STREAM_DRAW;
        }
        return GL_INVALID_VALUE;
    }

    inline GLenum DataTypeMap(DataType dtype)
    {
        switch (dtype)
        {
        case DataType::INT: return GL_INT;
        case DataType::FLOAT: return GL_FLOAT;
        case DataType::UINT: return GL_UNSIGNED_INT;
        case DataType::UCHAR: return GL_UNSIGNED_BYTE;
        }
        return GL_INVALID_VALUE;
    }
    
    class OpenGLVertexBuffer: public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const float* data, unsigned int size, BufferUseType utype);
        ~OpenGLVertexBuffer() override;

        void Bind() const override;

        void BufferData(const void* data, unsigned int size) const override;
    };

    class OpenGLIndexBuffer: public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const unsigned int* data, unsigned int size, BufferUseType utype);
        ~OpenGLIndexBuffer() override;

        void Bind() const override;

        void BufferData(const void* data, unsigned int size) const override;
    };
}
