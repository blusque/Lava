﻿#pragma once

namespace Lava
{
    class LAVA_API Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() {}

        virtual void Bind(int slot = 0) const = 0;

        virtual void SetData(void* data, uint32_t size) const = 0;

        static Ref<Texture> Create(const char* filename);

        static Ref<Texture> Create(uint32_t width, uint32_t height);
    
    protected:
        unsigned int m_RendererID { 0 };
        int m_Width { 0 };
        int m_Height { 0 };
        int m_Channels { 0 };
    };
}
