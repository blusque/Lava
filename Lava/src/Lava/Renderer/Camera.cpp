#include "lvpch.h"
#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    Camera::Camera(const ExtrinsicProps& extrinsicProps, PerspectiveType perspectiveType)
    {
        m_ExtrinsicProps = extrinsicProps;
        m_PerspectiveType = perspectiveType;

        m_PerspectiveIntrinsicProps = PerspectiveIntrinsicProps();
        m_OrthogonalIntrinsicProps = OrthogonalIntrinsicProps();

        m_ProjMatrix = std::vector<glm::mat4>(2);
        
        if (perspectiveType == Perspective)
        {
            m_ProjMatrix[perspectiveType] = glm::perspective(
                glm::radians(m_PerspectiveIntrinsicProps.FOV),
                m_AspectRatio,
                m_PerspectiveIntrinsicProps.Near,
                m_PerspectiveIntrinsicProps.Far);
        }
        else
        {
            auto const width_2 = m_AspectRatio * m_OrthogonalIntrinsicProps.Size * 0.5f;
            auto const height_2 = m_OrthogonalIntrinsicProps.Size * 0.5f;
            auto const nearVal = m_OrthogonalIntrinsicProps.Near;
            auto const farVal = m_OrthogonalIntrinsicProps.Far;
            m_ProjMatrix[perspectiveType] = glm::ortho(
                -width_2, width_2,
                -height_2, height_2,
                nearVal, farVal
            );
        }
        
        m_ViewMatrix = LookAt();
        m_VPMatrix = m_ProjMatrix[m_PerspectiveType] * m_ViewMatrix;
    }

    void Camera::SetPerspectiveType(PerspectiveType viewMethod)
    {
        m_PerspectiveType = viewMethod;

        if (m_PerspectiveType == Perspective)
        {
            UpdatePerspectiveIntrinsicProps(m_PerspectiveIntrinsicProps);
        }
        else
        {
            UpdateOrthogonalIntrinsicProps(m_OrthogonalIntrinsicProps);
        }
    }

    void Camera::UpdateExtrinsicProps(const ExtrinsicProps& props)
    {
        m_ExtrinsicProps = props;
        m_ViewMatrix = LookAt();
        UpdateVPMatrix();
    }

    void Camera::UpdatePerspectiveIntrinsicProps(const PerspectiveIntrinsicProps& props)
    {
        m_PerspectiveIntrinsicProps = props;
        m_ProjMatrix[Perspective] = glm::perspective(
            glm::radians(m_PerspectiveIntrinsicProps.FOV),
            m_AspectRatio,
            m_PerspectiveIntrinsicProps.Near,
            m_PerspectiveIntrinsicProps.Far
        );
        UpdateVPMatrix();
    }

    void Camera::UpdateAspectRatio(float AspectRatio)
    {
        m_AspectRatio = AspectRatio;

        if (m_PerspectiveType == Perspective)
        {
            UpdatePerspectiveIntrinsicProps(m_PerspectiveIntrinsicProps);
        }
        else
        {
            UpdateOrthogonalIntrinsicProps(m_OrthogonalIntrinsicProps);
        }
    }

    void Camera::UpdateOrthogonalIntrinsicProps(const OrthogonalIntrinsicProps& props)
    {
        m_OrthogonalIntrinsicProps = props;
        auto const width_2 = m_AspectRatio * m_OrthogonalIntrinsicProps.Size * 0.5f;
        auto const height_2 = m_OrthogonalIntrinsicProps.Size * 0.5f;
        auto const nearVal = m_OrthogonalIntrinsicProps.Near;
        auto const farVal = m_OrthogonalIntrinsicProps.Far;
        m_ProjMatrix[Orthogonal] = glm::ortho(
            -width_2, width_2,
            -height_2, height_2,
            nearVal, farVal
        );
        UpdateVPMatrix();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjMatrix() const
    {
        return m_ProjMatrix[m_PerspectiveType];
    }

    glm::mat4 Camera::GetVPMatrix() const
    {
        return m_VPMatrix;
    }

    Ref<Camera> Camera::Create(const ExtrinsicProps& extrinsicProps, PerspectiveType perspectiveType)
    {
        return CreateRef<Camera>(extrinsicProps, perspectiveType);
    }

    void Camera::UpdateVPMatrix()
    {
        m_VPMatrix = m_ProjMatrix[m_PerspectiveType] * m_ViewMatrix;
    }

    glm::mat4 Camera::LookAt() const
    {
        return lookAt(m_ExtrinsicProps.Position,
            m_ExtrinsicProps.Position + m_ExtrinsicProps.Orient,
            m_ExtrinsicProps.Up);
    }
}
