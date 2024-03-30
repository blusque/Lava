#pragma once

#include "Lava/Core.h"

namespace Lava
{
    class LAVA_API Input
    {
    public:
        static bool IsKeyPressed(unsigned int keycode);
        static bool IsMouseButtonPressed(unsigned int button);
        static std::pair<float, float> GetMousePos();
        static float GetMouseX();
        static float GetMouseY();
    };
}
