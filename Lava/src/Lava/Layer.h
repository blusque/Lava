#pragma once
#include "Events/Event.h"

namespace Lava
{
    class LAVA_API Layer
    {
    public:
        Layer(const std::string& layerName = "Lava Engine");
        virtual ~Layer() = default;

        virtual void OnAttach() const {}
        virtual void OnDetach() const {}
        virtual void OnUpdate() const {}
        virtual void OnEvent(Event* e) const {}

        const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}
