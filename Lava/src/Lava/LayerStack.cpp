#include "lvpch.h"
#include "LayerStack.h"

namespace Lava
{
    LayerStack::LayerStack()
    {
        m_Insert = m_LayerStack.begin();
    }

    LayerStack::~LayerStack()
    {
        for (auto&& l : m_LayerStack)
        {
            delete l;
        }
    }

    void LayerStack::Push(Layer* layer)
    {
        m_Insert = m_LayerStack.emplace(m_Insert, layer);
    }

    void LayerStack::PushBack(Layer* layer)
    {
        m_LayerStack.emplace_back(layer);
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
