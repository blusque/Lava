#pragma once
#include <glm/vec2.hpp>

#include "Texture.h"

namespace Lava
{
    class LAVA_API SubTexture
    {
    public:
        SubTexture(const Ref<Texture>& texture, const glm::vec2& elemSize,
            const glm::vec2& elemCoord, const glm::vec2& elemNum);
        ~SubTexture() = default;

        static Ref<SubTexture> Create(const Ref<Texture>& texture, const glm::vec2& elemSize,
            const glm::vec2& elemCoord, const glm::vec2& elemNum);

        Ref<Texture> GetTexture() const { return m_Texture; }
        glm::vec2 GetMaxCoord() const { return m_MaxCoord; }
        glm::vec2 GetMinCoord() const { return m_MinCoord; }
        
    private:
        Ref<Texture> m_Texture;
        glm::vec2 m_MaxCoord;
        glm::vec2 m_MinCoord;
    };
}
