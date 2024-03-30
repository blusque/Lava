#pragma once
#include <glm/glm.hpp>

#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/MouseEvent.h"
#include "Lava/Core/Timestep.h"

namespace Lava
{
    class LAVA_API Camera
    {
    public:
        struct InternalProps
        {
            float FOV { 45.f };
            float AspectRatio { 16.f / 9.f };
            float Near { 0.1f };
            float Far { 100.f };
        };

        struct ExternalProps
        {
            glm::vec3 Position { 0.f, 0.f, 0.f };
            glm::vec3 Orient { 0.f, 0.f, 1.f };
            glm::vec3 Up { 0.f, 1.f, 0.f };
        };
    
        Camera(const ExternalProps& externalParams);
        virtual ~Camera() = default;

        void UpdateExternalProps(const ExternalProps& props);
        void UpdateInternalProps(const InternalProps& props);

        [[nodiscard]] auto GetInternalProps() const { return m_InternalProps; }
        [[nodiscard]] auto GetExternalProps() const { return m_ExternalProps; }

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjMatrix() const;
        [[nodiscard]] glm::mat4 GetVPMatrix() const;
    
        static Ref<Camera> Create(const ExternalProps& externalParams);
    
    private:
        void UpdateVPMatrix();
    
    private:
        InternalProps m_InternalProps;
        ExternalProps m_ExternalProps;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_VPMatrix;
    };
}
