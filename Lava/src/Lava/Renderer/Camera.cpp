#include "lvpch.h"
#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    Camera::Camera(const ExternalProps& externalParams)
    {
        m_ExternalProps = externalParams;
        m_ProjMatrix = glm::perspective(glm::radians(m_InternalProps.FOV), m_InternalProps.AspectRatio, m_InternalProps.Near, m_InternalProps.Far);
        m_ViewMatrix = lookAt(m_ExternalProps.Position, m_ExternalProps.Position + m_ExternalProps.Orient, m_ExternalProps.Up);
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }

    void Camera::UpdateExternalProps(const ExternalProps& props)
    {
        m_ExternalProps = props;
        m_ViewMatrix = lookAt(m_ExternalProps.Position, m_ExternalProps.Position + m_ExternalProps.Orient, m_ExternalProps.Up);
        UpdateVPMatrix();
    }

    void Camera::UpdateInternalProps(const InternalProps& props)
    {
        m_InternalProps = props;
        m_ProjMatrix = glm::perspective(glm::radians(m_InternalProps.FOV), m_InternalProps.AspectRatio, m_InternalProps.Near, m_InternalProps.Far);
        UpdateVPMatrix();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjMatrix() const
    {
        return m_ProjMatrix;
    }

    glm::mat4 Camera::GetVPMatrix() const
    {
        return m_VPMatrix;
    }

    Ref<Camera> Camera::Create(const ExternalProps& externalParams)
    {
        return CreateRef<Camera>(externalParams);
    }

    void Camera::UpdateVPMatrix()
    {
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }
}
