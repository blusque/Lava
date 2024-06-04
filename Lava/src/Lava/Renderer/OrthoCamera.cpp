#include "lvpch.h"
#include "OrthoCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    OrthoCamera::OrthoCamera(const ExternalProps& externalProps)
    {
        m_ExternalProps = externalProps;
        auto const width_2 = m_InternalProps.AspectRatio * m_InternalProps.Height * 0.5f;
        auto const height_2 = m_InternalProps.Height * 0.5f;
        auto const nearVal = m_InternalProps.Near;
        auto const farVal = m_InternalProps.Far;
        m_ProjMatrix = glm::orthoNO(-width_2, width_2, -height_2, height_2, nearVal, farVal);
        auto constexpr Identity = glm::mat4(1.f);
        auto const RotMatrix = rotate(Identity, glm::radians(m_ExternalProps.Roll), glm::vec3(0.f, 0.f, 1.f));
        auto const TransMatrix = translate(Identity, m_ExternalProps.Position);
        m_ViewMatrix = inverse(RotMatrix * TransMatrix);

        UpdateVPMatrix();
    }

    Ref<OrthoCamera> OrthoCamera::Create(const ExternalProps& externalProps)
    {
        return CreateRef<OrthoCamera>(externalProps);
    }

    void OrthoCamera::UpdateExternalProps(const ExternalProps& props)
    {
        LV_PROFILE_FUNCTION();
        
        auto const dTrans = props.Position - m_ExternalProps.Position;
        auto const dRot = props.Roll - m_ExternalProps.Roll;
        m_ExternalProps = props;
        
        auto constexpr Identity = glm::mat4(1.f);
        auto const RotMatrix = rotate(Identity, dRot, glm::vec3(0.f, 0.f, 1.f));
        auto const TransMatrix = translate(Identity, dTrans);

        m_ViewMatrix = inverse(RotMatrix * TransMatrix) * m_ViewMatrix;
        
        UpdateVPMatrix();
    }


    void OrthoCamera::UpdateInternalProps(const InternalProps& props)
    {
        LV_PROFILE_FUNCTION();
        
        m_InternalProps = props;
        auto const width_2 = m_InternalProps.AspectRatio * m_InternalProps.Height * 0.5f;
        auto const height_2 = m_InternalProps.Height * 0.5f; 
        
        m_ProjMatrix = glm::ortho(-width_2, width_2, -height_2, height_2);

        UpdateVPMatrix();
    }

    glm::mat4 OrthoCamera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    glm::mat4 OrthoCamera::GetProjMatrix() const
    {
        return m_ProjMatrix;
    }

    glm::mat4 OrthoCamera::GetVPMatrix() const
    {
        return m_VPMatrix;
    }

    void OrthoCamera::UpdateVPMatrix()
    {
        LV_PROFILE_FUNCTION();
        
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }
}
