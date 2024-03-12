#pragma once
#include "Lava/Core/Layer.h"

namespace Lava
{
    class LAVA_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void Push(Layer* layer);
        void PushBack(Layer* layer);
        void Pop(const Layer* layer);
        void PopBack(const Layer* layer);

        std::list<Layer*>::iterator begin() { return m_LayerStack.begin(); }
        std::list<Layer*>::iterator end() { return m_LayerStack.end(); }
        std::list<Layer*>::reverse_iterator rbegin() { return m_LayerStack.rbegin(); }
        std::list<Layer*>::reverse_iterator rend() { return m_LayerStack.rend(); }
    private:
        std::list<Layer*> m_LayerStack;
        std::list<Layer*>::iterator m_Insert;
    };
}
