#include "lvpch.h"
#include "WindowsInput.h"

#ifdef LV_PLATFORM_WINDOWS

#include "GLFW/glfw3.h"
#include "Lava/Core/Application.h"

namespace Lava
{
    Input* Input::s_Instance = new WindowsInput;

    bool WindowsInput::IsKeyPressedImpl(unsigned keycode)
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto const action = glfwGetKey(window, static_cast<int>(keycode));

        return action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(unsigned button)
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto const action = glfwGetMouseButton(window, static_cast<int>(button));

        return action == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl() const
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { static_cast<float>(x), static_cast<float>(y) };
    }

    float WindowsInput::GetMouseXImpl() const
    {
        auto [x, y] = GetMousePosImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl() const
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }
}

#endif