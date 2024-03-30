#pragma once

namespace Lava
{
    class Entity;
    
    class Scene
    {
    public:

    private:
        std::unordered_map<std::string, Ref<Entity>> m_Entities;
    };
}
