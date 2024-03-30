﻿#pragma once

#include <random>

class Random
{
public:
    static int RandInt(int min, int max)
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
