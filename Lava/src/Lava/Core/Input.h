#pragma once

#include "Lava/Core.h"

namespace Lava
{
    class LAVA_API Input
    {
    public:
        virtual ~Input() {}
        static bool IsKeyPressed(unsigned int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        static bool IsMouseButtonPressed(unsigned int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        
    protected:
        virtual bool IsKeyPressedImpl(unsigned int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(unsigned int button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() const = 0;
        virtual float GetMouseXImpl() const = 0;
        virtual float GetMouseYImpl() const = 0;
        
    private:
        static Input* s_Instance;
    };
}
