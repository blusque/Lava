﻿#pragma once
#include "RenderAPI.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Lava/Renderer/Camera.h"

namespace Lava
{
    class LAVA_API Renderer
    {
    public:
        static void Init();

        static void Shutdown();

        static void ResizeCamera(unsigned width, unsigned height);
        
        static void BeginScene(const Ref<Camera>& cam);

        static void Submit(const Ref<VertexArray>& vao, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.f));
        
        static void EndScene();

        static RenderAPI::Platform GetPlatform();

    private:
        static glm::mat4 m_VPMatrix;
    };
}

