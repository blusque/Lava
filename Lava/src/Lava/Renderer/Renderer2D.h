#pragma once
#include "Lava/Renderer/Texture.h"
#include "Lava/Renderer/Camera.h"

#define ASSETS_ROOT "C:/Users/kokut/dev/Lava/Sandbox/assets/"
#define ASSETS_FILE(x) LV_STR(x)
#define ASSETS_PATH(x) LV_CONCAT(ASSETS_ROOT, ASSETS_FILE(x))

namespace Lava
{
    class LAVA_API Renderer2D
    {
    public:
        static void Init();

        static void Shutdown();
        
        static void BeginScene(const Ref<Camera>& cam);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float tillingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float tillingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));

        static void DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float tillingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
        static void DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float tillingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
        
        static void EndScene();
    };
}
