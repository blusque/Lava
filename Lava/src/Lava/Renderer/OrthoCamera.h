#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Lava
{
    class LAVA_API OrthoCamera
    {
    public:
        struct InternalProps
        {
            float Height { 1.f };
            float AspectRatio { 16.f / 9.f };
            float Near { -1.f };
            float Far { 1.f };
        };

        struct ExternalProps
        {
            glm::vec3 Position { 0.f };
            float Roll { 0.f };
        };
        
        OrthoCamera(const ExternalProps& externalProps);
        virtual ~OrthoCamera() = default;

        void UpdateExternalProps(const ExternalProps& props);
        void UpdateInternalProps(const InternalProps& props);

        [[nodiscard]] ExternalProps GetExternalProps() const { return m_ExternalProps; }
        [[nodiscard]] InternalProps GetInternalProps() const { return m_InternalProps; }

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjMatrix() const;
        [[nodiscard]] glm::mat4 GetVPMatrix() const;
        
        static Ref<OrthoCamera> Create(const ExternalProps& externalProps);
        
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
