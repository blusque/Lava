#pragma once
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
        virtual void OnUpdate() {}
        virtual void OnEvent(Event* e) {}

        const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}
