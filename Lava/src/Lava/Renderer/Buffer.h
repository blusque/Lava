#pragma once

namespace Lava
{
    enum class LAVA_API BufferType
    {
        VertexBuffer = 0,
        IndexBuffer = 1
    };
    
    enum class LAVA_API BufferUseType
    {
        STATIC = 0,
        DYNAMIC = 1,
        STREAM = 2
    };

    enum class LAVA_API DataType
    {
        FLOAT,
        INT,
        UINT,
        UCHAR
    };

    struct LayoutData
    {
        int Count { 0 };
        DataType Type { DataType::FLOAT };
        unsigned int Size { 0 };
        bool Normalized { false };

        static unsigned int GetSizeofType(DataType type)
        {
            if (type == DataType::FLOAT)
            {
                return sizeof(float);
            }
            if (type == DataType::UINT)
            {
                return sizeof(unsigned int);
            }
            if (type == DataType::UCHAR)
            {
                return sizeof(unsigned char);
            }
            if (type == DataType::INT)
            {
                return sizeof(int);
            }
            
            return 0;
        }
    };
    
    class BufferLayout
    {
    public:
        BufferLayout() = default;
        ~BufferLayout() = default;

        void Add(int count, DataType type, bool normalized, int stride = 0)
        {
            auto const size = LayoutData::GetSizeofType(type);
            m_Layout.push_back({ count, type, size, normalized});
            if (stride == 0)
            {
                m_Stride += count * static_cast<int>(size);
            }
            else
            {
                m_Stride = stride;
            }
        }

        [[nodiscard]] auto GetLayout() const
        {
            return m_Layout;
        }

        [[nodiscard]] auto GetStride() const
        {
            return m_Stride;
        }

    private:
        std::vector<LayoutData> m_Layout;
        int m_Stride { 0 };
    };

    using BufferLayoutPtr = std::shared_ptr<BufferLayout>;
    using BufferLayoutUPtr = std::unique_ptr<BufferLayout>;
    
    class IBuffer
    {
    public:
        virtual ~IBuffer() = default;
        
        virtual void Bind() const = 0;

        // virtual uint32_t GetID() const = 0;
        //
        // virtual uint32_t GetSize() const = 0;
        //
        // virtual int GetCount() const = 0;
        //
        // virtual int GetElementSize() const = 0;
        //
        // virtual BufferUseType GetUseType() const = 0;

        [[nodiscard]] virtual BufferType GetBufferType() const = 0;
    };

#define BUFFER_TYPE(type) BufferType GetBufferType() const override \
    { return BufferType::##type; }
    
    class LAVA_API VertexBuffer: public IBuffer
    {
    public:
        using ptr = std::shared_ptr<VertexBuffer>;
        using uptr = std::unique_ptr<VertexBuffer>;
        
        BUFFER_TYPE(VertexBuffer)

        VertexBuffer();
        ~VertexBuffer() override = default;

        void Bind() const override {}

        void AddLayout(int count, DataType type, bool normalized, int stride = 0) const
        {
            m_Layout->Add(count, type, normalized, stride);
        }

        [[nodiscard]] auto GetLayout() const
        {
            return m_Layout->GetLayout();
        }

        [[nodiscard]] auto GetStride() const
        {
            return m_Layout->GetStride();
        }

        static VertexBuffer::ptr Create(float* data, uint32_t size, BufferUseType utype);

    protected:
        unsigned int m_RendererID { 0 };
        BufferLayoutUPtr m_Layout;
        unsigned int m_Size { 0 };
    };

    class LAVA_API IndexBuffer: public IBuffer
    {
    public:
        using ptr = std::shared_ptr<IndexBuffer>;
        using uptr = std::unique_ptr<IndexBuffer>;
        
        BUFFER_TYPE(IndexBuffer)

        ~IndexBuffer() override = default;
        
        void Bind() const override {}

        [[nodiscard]] virtual unsigned GetCount() const
        {
            return m_Count;
        }

        static IndexBuffer::ptr Create(unsigned int* data, uint32_t size, BufferUseType utype);

    protected:
        unsigned int m_RendererID { 0 };
        unsigned int m_Size { 0 };
        unsigned int m_Count { 0 };
    };
    
    // class VertexBufferFactory
    // {
    // public:
    //     static VertexBufferFactory& GetFactory()
    //     {
    //         static VertexBufferFactory factory;
    //         return factory;
    //     }
    //     
    //     virtual ~VertexBufferFactory() = default;
    //
    //     VertexBuffer* Create(float* data, uint32_t size, BufferUseType utype);
    // };
    //
    // class IndexBufferFactory
    // {
    // public:
    //     static IndexBufferFactory& GetFactory()
    //     {
    //         static IndexBufferFactory factory;
    //         return factory;
    //     }
    //     
    //     virtual ~IndexBufferFactory() = default;
    //
    //     IndexBuffer* Create(unsigned int* data, uint32_t size, BufferUseType utype);
    // };
}
