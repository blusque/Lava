﻿#pragma once

namespace Lava
{
    class LAVA_API Timestep
    {
    public:
        Timestep(float time = 0.f): m_Time(time) {}

        operator float() const { return m_Time; }

        [[nodiscard]] float GetSeconds() const { return m_Time; }
        [[nodiscard]] float GetMilliseconds() const { return m_Time * 1000.f; }
        
    private:
        float m_Time;
    };
}
