#include "lvpch.h"
#include "CameraComponent.h"

namespace Lava
{
    CameraComponent::CameraComponent(const Ref<Lava::Camera>& camera, bool isActive)
        : Camera(camera), IsActive(isActive)
    {
    }

    void CameraComponent::UpdateExtrinsicProps(const TransformComponent& trans) const
    {
        auto props = Camera::ExtrinsicProps();
        props.Position = trans.Position;
        auto const rotMat = glm::mat3(trans.GetRotMat());
        props.Orient = rotMat * props.Orient;
        props.Up = rotMat * props.Up;
        
        Camera->UpdateExtrinsicProps(props);
    }
}
