#pragma once
#include <list>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Lava/Core.h"
#include "Lava/Core/Timestep.h"

struct ParticleProps
{
    glm::vec2 Position { 0.f };
    float Rotation { 0.f };
    glm::vec2 Size { 10.f };
    float SizeVariant { 5.f };
    
    glm::vec2 Velocity { 50.f };
    glm::vec2 VelocityVariant { 30.f };
    
    float AngularVelocity { 30.f };
    
    glm::vec4 BeginColor { 0.9f, 0.9f, 0.f, 1.f};
    glm::vec4 EndColor { 0.6f, 0.3f, 0.2f, 1.f};
    
    float Lifetime { 1.f };
};

namespace ParticleUtils
{
    template <typename Ty>
    Ty lerp(Ty begin, Ty end, float duration, float now)
    {
        now = now / duration;
        return (1.f - now) * begin + now * end;
    }
}

class ParticleSystemComponent
{
public:
    ParticleSystemComponent();
    ~ParticleSystemComponent() = default;
    
    void OnUpdate(Lava::Timestep ts);
    
    void Emit(int num = 5);

    auto GetParticlePool() const { return m_ParticlePool; }

    ParticleProps& GetParticleProps() { return m_ParticleProps; }

private:
    class Particle
    {
    public:
        Particle() = default;
        ~Particle() = default;
    
        void OnUpdate(Lava::Timestep ts);
        
        glm::vec2 Position { 0.f };
        float Rotation { 0.f };
        glm::vec2 Size { 0.f };
        
        glm::vec2 Velocity { 0.f };
        float AngularVelocity { 0.f };
        
        glm::vec4 BeginColor { 0.f };
        glm::vec4 EndColor { 0.f };
        glm::vec4 Color { 0.f };

        float Lifetime { 0.f };
        float AccumulateTime { 0.f };

        bool IsAlive { false };
    };

    ParticleProps m_ParticleProps;
    uint32_t m_TotalParticleNum { 1000 };
    uint32_t m_ParticleIndex { 0 };
    std::vector<Particle> m_ParticlePool;
};
