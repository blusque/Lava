#pragma once

#include "GLFW/glfw3.h"
#include "Lava/Window.h"

namespace Lava
{
    struct WindowData
    {
        int Width;
        int Height;
        const char* Title;
        bool VSync;
        Window::EventFn CallbackFn;
    };
    
    class WindowsWindow: public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        int GetWidth() const override;
        int GetHeight() const override;

        void SetEventCallback(const EventFn& callback) override;
        void SetVSync(bool enable) override;
        bool IsVSync() const override;

    private:
        void Init(const WindowProps& props);
        void Shutdown() const;

    private:
        WindowData m_Data;
        GLFWwindow* m_Window;
        static bool s_GLFWInitialized;
    };
}

