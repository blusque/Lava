#include "lvpch.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "Lava/Core/Application.h"

namespace Lava
{
    bool Input::IsKeyPressed(unsigned keycode)
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto const action = glfwGetKey(window, static_cast<int>(keycode));

        return action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(unsigned button)
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto const action = glfwGetMouseButton(window, static_cast<int>(button));

        return action == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePos()
    {
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { static_cast<float>(x), static_cast<float>(y) };
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePos();
        return x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePos();
        return y;
    }    
}
