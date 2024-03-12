#pragma once
#include "Lava/Core/Layer.h"
#include "Lava/Events/ApplicationEvent.h"
#include "imgui.h"

namespace Lava
{
    class LAVA_API ImGuiLayer: public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnGuiRender() override;

        static void OnBegin();
        static void OnEnd();
        
// According to ImGui:
// DLL users:
// - Heaps and globals are not shared across DLL boundaries!
// - You will need to call SetCurrentContext() + SetAllocatorFunctions() for each static/DLL boundary you are calling from.
// - Same applies for hot-reloading mechanisms that are reliant on reloading DLL (note that many hot-reloading mechanisms work without DLL).
// - Using Dear ImGui via a shared library is not recommended, because of function call overhead and because we don't guarantee backward nor forward ABI compatibility.
// - Confused? In a debugger: add GImGui to your watch window and notice how its value changes depending on your current location (which DLL boundary you are in).
        static ImGuiContext* GetCurrentContext();
    
    private:
        float m_Time { 0.f };
    };
}

