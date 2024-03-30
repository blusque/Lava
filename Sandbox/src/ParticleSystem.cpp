#include "ParticleSystem.h"

#include <execution>
#include <glm/ext/matrix_transform.hpp>

#include "Random.h"
#include "Lava/Renderer/Renderer2D.h"

void ParticleSystemComponent::Particle::OnUpdate(Lava::Timestep ts)
{
    if (IsAlive)
    {
        Position += Velocity * static_cast<float>(ts);
        Rotation += AngularVelocity * ts;
        if (BeginColor != EndColor)
        {
            Color = ParticleUtils::lerp(BeginColor, EndColor, Lifetime, AccumulateTime);
        }
        else
        {
            Color = BeginColor;
        }

        if (BeginSize != EndSize)
        {
            Size = ParticleUtils::lerp(BeginSize, EndSize, Lifetime, AccumulateTime);
        }
        else
        {
            Size = BeginSize;
        }
        AccumulateTime += ts;
    }
}

ParticleSystemComponent::ParticleSystemComponent()
{
    m_ParticlePool.resize(m_TotalParticleNum);
}

void ParticleSystemComponent::OnUpdate(Lava::Timestep ts)
{
    for (auto&& particle : m_ParticlePool)
    {
        if (particle.IsAlive)
        {
            particle.OnUpdate(ts);
            if (particle.AccumulateTime > m_ParticleProps.Lifetime)
            {
                particle.IsAlive = false;
            }
        }
    }
}

void ParticleSystemComponent::OnRender(const Lava::Ref<Lava::OrthoCamera>& camera) const
{
    Lava::Renderer2D::BeginScene(camera);

    for (auto&& particle : m_ParticlePool)
    {
        if (particle.IsAlive)
        {
            Lava::Renderer2D::DrawRotateQuad(
                particle.Position, particle.Rotation, particle.Size, particle.Color);
        }
    }
    
    Lava::Renderer2D::EndScene();
}

void ParticleSystemComponent::Emit(int num)
{
    for (auto i = 0; i < num; i++)
    {
        auto& particle = m_ParticlePool[m_ParticleIndex];

        particle.IsAlive = true;
        particle.Position = m_ParticleProps.Position;
        particle.Rotation = m_ParticleProps.Rotation + Random::Rand(-90.f, 90.f);

        particle.BeginSize = m_ParticleProps.BeginSize + m_ParticleProps.SizeVariant * (2 * Random::Rand() - 1.f);
        particle.EndSize = m_ParticleProps.EndSize;

        particle.BeginColor = m_ParticleProps.BeginColor;
        particle.EndColor = m_ParticleProps.EndColor;

        particle.Velocity = m_ParticleProps.Velocity;
        particle.Velocity.x += m_ParticleProps.VelocityVariant.x * (2 * Random::Rand() - 1.f);
        particle.Velocity.y += m_ParticleProps.VelocityVariant.y * (2 * Random::Rand() - 1.f);

        particle.AngularVelocity = m_ParticleProps.AngularVelocity;

        particle.AccumulateTime = 0.f;
        particle.Lifetime = m_ParticleProps.Lifetime;

        m_ParticleIndex = ++m_ParticleIndex % m_TotalParticleNum;
    }
}
