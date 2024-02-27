#pragma once
#include "Lava/Core/Timestep.h"
#include "Events/Event.h"

namespace Lava
{
    class LAVA_API Layer
    {
    public:
        Layer(const std::string& layerName = "Lava Engine");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event* e) {}
        virtual void OnGuiRender() {}

        const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}
