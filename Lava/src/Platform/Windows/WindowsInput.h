#pragma once
#ifdef LV_PLATFORM_WINDOWS

#include "Lava/Core/Input.h"

namespace Lava
{
    class WindowsInput: public Input
    {
    public:
        bool IsKeyPressedImpl(unsigned keycode) override;
        bool IsMouseButtonPressedImpl(unsigned button) override;
        std::pair<float, float> GetMousePosImpl() const override;
        float GetMouseXImpl() const override;
        float GetMouseYImpl() const override;
    };
}

#endif