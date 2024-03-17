#pragma once
#include <list>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Lava/Core.h"
#include "Lava/Core/Timestep.h"

class Particle
{
public:
    Particle(const glm::vec2& pos, float rot, const glm::vec2& scale, const glm::vec2& vel, float avel, float lifetime = 1.f);
    ~Particle() = default;
    
    void OnUpdate(Lava::Timestep ts);

    glm::vec2 GetPosition() const { return m_Position; }
    float GetRotation() const { return m_Rotation; }
    glm::vec2 GetScale() const { return m_Scale; }
    glm::vec4 GetColor() const { return m_Color; }

    float GetAccumulateTime() const { return m_AccumulateTime; }
    float GetLifetime() const { return m_Lifetime; } 

private:
    glm::vec2 m_Position;
    float m_Rotation;
    glm::vec2 m_Scale;
    glm::vec2 m_Velocity;
    float m_AngularVelocity;
    glm::vec4 m_Color { 0.6f, 0.6f, 0.6f, 1.f};

    float m_AccumulateTime;
    float m_Lifetime;
};

class ParticleSystemComponent
{
public:
    ParticleSystemComponent() = default;
    ~ParticleSystemComponent() = default;
    
    void OnUpdate(Lava::Timestep ts);
    
    void Spawn(glm::vec2 position, float rotation, int num = 5, float lifetime = 1.f);

    auto GetParticles() const { return m_Particles; }

private:
    std::list<Lava::Ref<Particle>> m_Particles;
};
