#pragma once

#ifdef LV_PLATFORM_WINDOWS

#include "GLFW/glfw3.h"
#include "Lava/Core/Window.h"
#include "Lava/Renderer/GraphicsContext.h"

namespace Lava
{
    class IGraphicsContext;

    class FGraphicsContext;
    
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
        WindowsWindow(const WindowProps& props, IGraphicsContext* graphicsContext);
        ~WindowsWindow() override;

        void OnUpdate() override;

        int GetWidth() const override;
        int GetHeight() const override;

        void SetEventCallback(const EventFn& callback) override;
        void SetVSync(bool enable) override;
        bool IsVSync() const override;
        void* GetNativeWindow() const override;

    private:
        void Init(const WindowProps& props, IGraphicsContext* graphicsContext);
        void Shutdown() const;

    private:
        WindowData m_Data;
        GLFWwindow* m_Window;
        IGraphicsContextUPtr m_Context;
        static bool s_GLFWInitialized;
    };
}
#endif
