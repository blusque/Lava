#include "ParticleSystem.h"

#include <glm/ext/matrix_transform.hpp>

#include "Random.h"

Particle::Particle(const glm::vec2& pos, float rot, const glm::vec2& scale, const glm::vec2& vel, float avel, float lifetime)
{
    m_Position = pos;
    m_Rotation = rot;
    m_Scale = scale;
    m_Velocity = vel;
    m_AngularVelocity = avel;
    m_AccumulateTime = 0.f;
    m_Lifetime = lifetime;
}

void Particle::OnUpdate(Lava::Timestep ts)
{
    m_Position += m_Velocity * static_cast<float>(ts);
    m_Rotation += m_AngularVelocity * ts;
    m_AccumulateTime += ts;
}

void ParticleSystemComponent::OnUpdate(Lava::Timestep ts)
{
    for (auto it = m_Particles.begin(); it != m_Particles.end();)
    {
        (*it)->OnUpdate(ts);
        if ((*it)->GetAccumulateTime() > (*it)->GetLifetime())
        {
            auto const now = it;
            ++it;
            m_Particles.erase(now);
        }
        ++it;
    }
}

void ParticleSystemComponent::Spawn(glm::vec2 position, float rotation, int num, float lifetime)
{
    for (auto i = 0; i < num; i++)
    {
        auto const rot = Random::Rand(-180.f, 180.f);
        auto const scale = glm::vec2(Random::Rand(3.f, 10.f));
        auto const angle = glm::radians(Random::Rand(rotation - 80.f, rotation + 80.f));
        auto const speed = -Random::Rand(10.f, 100.f);
        auto const vel = glm::vec2(speed * cos(angle), speed * sin(angle));
        auto const avel = Random::Rand(-200.f, 200.f);

        m_Particles.emplace_back(Lava::CreateRef<Particle>(position, rot, scale, vel, avel, lifetime));
    }
}
