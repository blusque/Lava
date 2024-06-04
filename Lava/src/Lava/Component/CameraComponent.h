#pragma once
#include "TransformComponent.h"
#include "Lava/Renderer/Camera.h"

namespace Lava
{
    struct LAVA_API CameraComponent
    {
        Ref<Camera> Camera;
        bool IsActive;
        
        CameraComponent(const Ref<Lava::Camera>& camera = Camera::Create(), bool isActive = false);

        void UpdateExtrinsicProps(const TransformComponent& trans) const;
    };
}
