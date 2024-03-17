#pragma once
#include <random>

class Random
{
public:
    template <typename Ty = int>
    static int RandInt(Ty min, Ty max)
    {
        auto ud = std::uniform_int_distribution(min, max);
        return ud(m_Random);
    }

    template <typename Ty = float>
    static float Rand(Ty min, Ty max)
    {
        auto ud = std::uniform_real_distribution(min, max);
        return ud(m_Random);
    }
    
private:
    static std::mt19937 m_Random;
};
