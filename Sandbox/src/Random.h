#pragma once

#include <random>

class Random
{
public:
    static int RandInt(int min, int max)
    {
        auto ud = std::uniform_int_distribution(std::random_device{}());
        return ud();
    }

private:
    std::mt19937 m_Random;
};
