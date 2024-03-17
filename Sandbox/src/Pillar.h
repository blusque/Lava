#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Lava/Core/Timestep.h"
#include "Lava/Events/Event.h"
#include "Lava/Events/KeyboardEvent.h"
#include "Lava/Renderer/Texture.h"


class Pillar
{
public:
    Pillar(glm::vec3 upPosition, glm::vec3 downPosition);
    ~Pillar() = default;
    
    void OnBegin();
    void OnUpdate(Lava::Timestep ts);
    void OnGuiRender();
    void OnEvent(Lava::Event* e);

    glm::vec3 GetUpPillarPosition() const { return m_Position.first; }
    glm::vec3 GetDownPillarPosition() const  { return m_Position.second; }
    glm::vec2 GetScale() const { return m_Scale; }
    Lava::Ref<Lava::Texture> GetTexture() const { return m_Texture; }

private:
    std::pair<glm::vec3, glm::vec3> m_Position;
    glm::vec2 m_Scale { 512.f, 512.f };
    Lava::Ref<Lava::Texture> m_Texture;
};
