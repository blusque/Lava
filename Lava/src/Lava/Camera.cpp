#include "lvpch.h"
#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    Camera::Camera(const CameraBox& param)
        : m_Box(param), m_ViewMatrix(1.f)
    {
        // m_Position = glm::vec3(0.f, 0.f, 0.f);
        // m_Rotation = glm::vec3(0.f, 0.f, 0.f);
        m_ProjMatrix = glm::ortho(m_Box.left, m_Box.right, m_Box.bottom, m_Box.top);
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }

    void Camera::SetPosition(const glm::vec3& position)
    {
        auto const dTrans = position - m_Position;
        m_Position = position;
        // m_ViewMatrix = inverse(translate(m_ViewMatrix, dTrans));
        UpdateVPMatrix(dTrans, 0.f);
    }

    // void Camera::SetRotation(const glm::vec3& rotation)
    // {
    //     m_Rotation = rotation;
    //     UpdateVPMatrix();
    // }
    void Camera::SetRotation(float rotation)
    {
        auto const dRot = rotation - m_Rotation.z;
        m_Rotation.z = rotation;
        // m_ViewMatrix = inverse(rotate(m_ViewMatrix, dRot, glm::vec3(0.f, 0.f, 1.f)));
        UpdateVPMatrix({ 0.f, 0.f, 0.f }, dRot);
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

    Ref<Camera> Camera::Create(const CameraBox& param)
    {
        return std::make_shared<Camera>(param);
    }

    void Camera::UpdateVPMatrix(const glm::vec3& dTrans, float dRot)
    {
        // auto const angle = length(m_Rotation);
        auto constexpr Identity = glm::mat4(1.f);
        auto const RotMatrix = rotate(Identity, dRot, glm::vec3(0.f, 0.f, 1.f));
        auto const TransMatrix = translate(Identity, dTrans);

        m_ViewMatrix = inverse(RotMatrix * TransMatrix) * m_ViewMatrix;
        
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }
}
