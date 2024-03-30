#include "lvpch.h"
#include "StaticMeshComponent.h"

namespace Lava
{
    StaticMeshComponent::StaticMeshComponent(const void* data, uint32_t dataSize,
        const uint32_t* indices, uint32_t indicesSize)
    {
        VAO = VertexArray::Create();
        auto const vbo = VertexBuffer::Create(data, dataSize, BufferUseType::DYNAMIC);
        vbo->AddLayout(3, DataType::FLOAT, false);
        vbo->AddLayout(3, DataType::FLOAT, false);
        VAO->AddVertexBuffer(vbo);
        auto const ibo = IndexBuffer::Create(indices, indicesSize, BufferUseType::DYNAMIC);
        VAO->SetIndexBuffer(ibo);
    }
}
