#pragma once
#include <glm/glm.hpp>

namespace Lava
{
    struct CameraFOV
    {
        float FOV;
        float Aspect;
        float Far;
        float Near;
    };

    struct CameraBox
    {
        float left;
        float right;
        float bottom;
        float top;
    };
    
    class LAVA_API Camera
    {
    public:
        Camera(const CameraBox& param);
        virtual ~Camera() {}

        void SetPosition(const glm::vec3& position);
        // void SetRotation(const glm::vec3& rotation);
        void SetRotation(float rotation);

        [[nodiscard]] glm::vec3 GetPosition() const { return m_Position; }
        [[nodiscard]] float GetRotation() const { return m_Rotation.z; }

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjMatrix() const;
        [[nodiscard]] glm::mat4 GetVPMatrix() const;
        
        static Ref<Camera> Create(const CameraBox& param);
    private:
        void UpdateVPMatrix(const glm::vec3& dTrans, float dRot);
    private:
        CameraBox m_Box;
        // glm::vec3 m_Rotation;   // axis-angle representation
        glm::vec3 m_Rotation { 0.f };
        glm::vec3 m_Position { 0.f };

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_VPMatrix;
    };
}
