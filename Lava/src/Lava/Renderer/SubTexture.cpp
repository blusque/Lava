#include "lvpch.h"
#include "SubTexture.h"

namespace Lava
{
    SubTexture::SubTexture(const Ref<Texture>& texture, const glm::vec2& elemSize, const glm::vec2& elemCoord,
        const glm::vec2& elemNum)
    {
        m_Texture = texture;
        auto const texSize = glm::vec2(m_Texture->GetWidth(), m_Texture->GetHeight());
        auto const resizeRate = elemSize / texSize;
        m_MaxCoord = (elemCoord + elemNum) * resizeRate;
        m_MinCoord = elemCoord * resizeRate;
    }

    Ref<SubTexture> SubTexture::Create(const Ref<Texture>& texture, const glm::vec2& elemSize,
        const glm::vec2& elemCoord, const glm::vec2& elemNum)
    {
        return CreateRef<SubTexture>(texture, elemSize, elemCoord, elemNum);
    }
}
