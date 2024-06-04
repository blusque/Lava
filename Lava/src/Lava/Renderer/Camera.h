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
        enum View
        {
            Perspective = 0,
            Orthogonal = 1
        };

        struct PerspectiveIntrinsicProps
        {
            float FOV { 45.f };
            float Near { 0.01f };
            float Far { 1000.f };
        };

        struct OrthogonalIntrinsicProps
        {
            float Size { 10.f };
            float Near { 0.f };
            float Far { 100.f };
        };

        struct ExtrinsicProps
        {
            glm::vec3 Position { 0.f, 0.f, 0.f };
            glm::vec3 Orient { 0.f, 0.f, 1.f };
            glm::vec3 Up { 0.f, 1.f, 0.f };
        };
    
        Camera(const ExtrinsicProps& extrinsicProps, View viewMethod);
        virtual ~Camera() = default;

        void SetViewMethod(View viewMethod);
        void UpdateExtrinsicProps(const ExtrinsicProps& props);
        void UpdatePerspectiveIntrinsicProps(const PerspectiveIntrinsicProps& props);
        void UpdateAspectRatio(float AspectRatio);
        void UpdateOrthogonalIntrinsicProps(const OrthogonalIntrinsicProps& props);

        View GetViewMethod() const { return m_ViewMethod; }
        decltype(auto) GetPerspectiveIntrinsicProps() const { return m_PerspectiveIntrinsicProps; }
        decltype(auto) GetOrthogonalIntrinsicProps() const { return m_OrthogonalIntrinsicProps; }
        float GetAspectRatio() const { return m_AspectRatio; }
        decltype(auto) GetExtrinsicProps() const { return m_ExtrinsicProps; }

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjMatrix() const;
        [[nodiscard]] glm::mat4 GetVPMatrix() const;
    
        static Ref<Camera> Create(const ExtrinsicProps& extrinsicProps = ExtrinsicProps(), View viewMethod = Perspective);
    
    private:
        void UpdateVPMatrix();

        glm::mat4 LookAt() const;
    
    private:
        View m_ViewMethod;
        PerspectiveIntrinsicProps m_PerspectiveIntrinsicProps;
        OrthogonalIntrinsicProps m_OrthogonalIntrinsicProps;
        float m_AspectRatio { 16.f / 9.f };
        ExtrinsicProps m_ExtrinsicProps;

        glm::mat4 m_ViewMatrix;
        std::vector<glm::mat4> m_ProjMatrix;
        glm::mat4 m_VPMatrix;
    };
}
