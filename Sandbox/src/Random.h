#pragma once
#include <random>
#include <glm/vec2.hpp>

class Random
{
public:
    template <typename Ty = int>
    static int RandInt(Ty min, Ty max)
    {
        auto ud = std::uniform_int_distribution(min, max);
        return ud(m_Random);
    }
    
    static float Rand(float min = 0.f, float max = 1.f)
    {
        auto ud = std::uniform_real_distribution(min, max);
        return ud(m_Random);
    }
    
private:
    static std::mt19937 m_Random;
};
