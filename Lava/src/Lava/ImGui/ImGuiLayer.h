#pragma once
#include "Lava/Layer.h"

namespace Lava
{
    class LAVA_API ImGuiLayer: public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event* e) override;

    private:
        float m_Time { 0.f };
    };
}

