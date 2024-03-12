#include "lvpch.h"
#include "Lava/Core/LayerStack.h"

namespace Lava
{
    LayerStack::LayerStack()
    {
        LV_PROFILE_FUNCTION();
        
        m_Insert = m_LayerStack.begin();
    }

    LayerStack::~LayerStack()
    {
        LV_PROFILE_FUNCTION();
        
        for (auto&& l : m_LayerStack)
        {
            delete l;
        }
    }

    void LayerStack::Push(Layer* layer)
    {
        m_Insert = m_LayerStack.emplace(m_Insert, layer);
        ++m_Insert;
    }

    void LayerStack::PushBack(Layer* layer)
    {
        m_LayerStack.emplace_back(layer);
        if (m_LayerStack.size() == 1)
        {
            m_Insert = m_LayerStack.begin();
        }
    }

    void LayerStack::Pop(const Layer* layer)
    {
        for (auto const it = m_LayerStack.begin(); it != m_LayerStack.end();)
        {
            if (*it == layer)
            {
                m_LayerStack.erase(it);
                --m_Insert;
                break;
            }
        }
    }

    void LayerStack::PopBack(const Layer* layer)
    {
        for (auto const it = m_LayerStack.begin(); it != m_LayerStack.end();)
        {
            if (*it == layer)
            {
                m_LayerStack.erase(it);
                break;
            }
        }
    }
}
