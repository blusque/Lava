#pragma once
#include "Events/Event.h"

namespace Lava
{
    struct WindowProps
    {
        const char* title { "Lava Engine" };
        int width { 1980 };
        int height { 1080 };
        bool VSync { true };
        
        WindowProps(const char* title = "Lava Engine", int width = 1920, int height = 1080)
            : title(title), width(width), height(height) {}
    };
    
    class LAVA_API Window
    {
    public:
        using EventFn = std::function<void(Event*)>;
        
        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        virtual void SetEventCallback(const EventFn& callback) = 0;
        virtual void SetVSync(bool enable) = 0;
        virtual bool IsVSync() const = 0;

        static [[nodiscard]] Window* Create(const WindowProps& props = WindowProps());
    };

    using WindowPtr = std::shared_ptr<Window>;
    using WindowUPtr = std::unique_ptr<Window>;
}
