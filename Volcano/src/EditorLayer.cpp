#include "EditorLayer.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lava/Component/CameraComponent.h"
#include "Lava/Component/ColorComponent.h"
#include "Lava/Component/MaterialComponent.h"
#include "Lava/Component/NameComponent.h"
#include "Lava/Component/RenderableComponent.h"
#include "Lava/Component/ScaleComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"
#include "Lava/Core/Random.h"
#include "Lava/Debug/Instrumentor.h"
#include "Lava/Renderer/Renderer2D.h"

namespace Lava
{
    union ImVec2ToGLMVec2
    {
        ImVec2 Im { 1280.f, 720.f };
        glm::vec2 GLM;
    };

    void EditorLayer::OnAttach()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnAttach();

        // m_PrimaryCamera = m_SceneCamera;
        m_MainScene = CreateRef<Scene>();
        m_SceneEntitiesPanel = CreateRef<SceneEntitiesPanel>(m_MainScene);
        
        auto const ParallelLight = m_MainScene->AddLightSource("ParallelLight", LightSourceComponent::Kind::Parallel,
        glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ -0.2f, -1.0f, -0.3f });
        auto const PointLight = m_MainScene->AddLightSource("PointLight", LightSourceComponent::Kind::Point,
        glm::vec3{ 1.5f, 0.8f, 3.f}, glm::vec3{ 0.f, 0.f, 0.f });
        auto const SpotLight = m_MainScene->AddLightSource("SpotLight", LightSourceComponent::Kind::Spot,
        m_SceneCamera->GetExtrinsicProps().Position, m_SceneCamera->GetExtrinsicProps().Orient);
        auto const container = Texture::Create(ASSETS_PATH(textures/container2.png));
        auto const specular = Texture::Create(ASSETS_PATH(textures/container2_specular.png));

        float const cube[] = {
            -0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,

             0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,

             0.5f, -0.5f,  0.5f,  1.f,  0.f,  0.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  1.f,  0.f,  0.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,

            -0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f,  0.5f, -1.f,  0.f,  0.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f,  0.5f, -1.f,  0.f,  0.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            
            -0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            
            -0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 0.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 1.0f, 0.0f, // 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, 1.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, 0.0f, 1.0f, // 1.f, 1.f, 1.f, 1.f,
        };

        uint32_t const indices[] = {
            0,  1,  2,
            2,  3,  0,

            4,  5,  6,
            6,  7,  4,

            8,  9,  10,
            10, 11, 8,
            
            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
        };

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        
        auto const coralMaterial = PhongMaterial::Instance(
                        { 1.f, 0.5f, 0.3f },
                        { 0.5f, 0.5f, 0.5f },
                        1.f
                    );
        auto const wallMaterial = PhongMaterial::Instance(
                        { 0.4f, 0.2f, 0.3f },
                        { 0.5f, 0.5f, 0.5f },
                        1.f
                    );
        auto const containerMaterial = PhongMaterial::Instance(container, specular, 1.f);

        for (int i = 0; i < 3; i++)
        {
            auto const rotX = Random::Rand(-90.f, 90.f);
            auto const rotY = Random::Rand(-90.f, 90.f);
            auto const rotZ = Random::Rand(-90.f, 90.f);
            auto const Cube = m_MainScene->AddEntity("Cube" + std::to_string(i), cubePositions[i],
                    glm::vec3{ rotX, rotY, rotZ });
            Cube->AddComponent<StaticMeshComponent>(cube, sizeof(cube), indices, sizeof(indices));
            Cube->AddComponent<TransformComponent>(
                    cubePositions[i],
                    glm::vec3{ rotX, rotY, rotZ }
                );
            Cube->AddComponent<ScaleComponent>(
                    glm::vec3 { 1.f, 1.f, 1.f }
                );
            Cube->AddComponent<MaterialComponent>(containerMaterial);
            // Cube->AddComponent<MaterialComponent>(coralMaterial);
            Cube->AddComponent<RenderableComponent>();
        }

        auto const Floor = m_MainScene->AddEntity("Floor", glm::vec3{ 0.f, -3.5f, -10.f },
                glm::vec3{ 0.f, 0.f, 0.f });
        Floor->AddComponent<StaticMeshComponent>(cube, sizeof(cube), indices, sizeof(indices));
        Floor->AddComponent<TransformComponent>(
                glm::vec3{ 0.f, -3.5f, -10.f },
                glm::vec3{ 0.f, 0.f, 0.f }
            );
        Floor->AddComponent<ScaleComponent>(
                glm::vec3 { 100.f, 1.f, 100.f }
            );
        Floor->AddComponent<MaterialComponent>(coralMaterial);
        Floor->AddComponent<RenderableComponent>();
        
        ParallelLight->AddComponent<TransformComponent>(
                glm::vec3{ 0.f, 0.f, 0.f },
                glm::vec3{ -0.2f, -1.0f, -0.3f }
            );
        ParallelLight->AddComponent<ColorComponent>(glm::vec4(0.6f));
        
        PointLight->AddComponent<StaticMeshComponent>(cube, sizeof(cube), indices, sizeof(indices));
        PointLight->AddComponent<TransformComponent>(
                glm::vec3{ 1.5f, 0.8f, 3.f},
                glm::vec3{ 0.f, 0.f, 0.f }
            );
        PointLight->AddComponent<ScaleComponent>(
                glm::vec3{ 0.4f, 0.4f, 0.4f }
            );
        PointLight->AddComponent<ColorComponent>(glm::vec4(0.4f));

        SpotLight->AddComponent<TransformComponent>(
                m_SceneCamera->GetExtrinsicProps().Position,
                m_SceneCamera->GetExtrinsicProps().Orient
            );
        SpotLight->AddComponent<ColorComponent>(glm::vec4(0.6f));

        auto Camera0 = m_MainScene->AddEntity("Camera0");
        Camera0->AddComponent<CameraComponent>();
        // Camera0->GetComponent<CameraComponent>().IsActive = true;
        // m_SceneCameraController->Active(false);
        // m_SceneCameraController->SetViewMethod(Camera::Orthogonal);

        m_ShaderLibrary = CreateRef<ShaderLibrary>();
        auto const flatColorShader = Shader::Create();
        auto texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/FlatColor.glsl));
        flatColorShader->Compile(texShaderProgram);
        m_ShaderLibrary->Add(flatColorShader);
        auto const shadowShader = Shader::Create();
        texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/Shadow.glsl));
        shadowShader->Compile(texShaderProgram);
        m_ShaderLibrary->Add(shadowShader);
        auto const postprocessingShader = Shader::Create();
        texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/PostProcessing.glsl));
        postprocessingShader->Compile(texShaderProgram);
        m_ShaderLibrary->Add(postprocessingShader);
        
        m_Texture = Texture::Create(ASSETS_PATH(textures/ChernoLogo.png));
        m_WindowWidth = Application::Get()->GetWindow()->GetWidth();
        m_WindowHeight = Application::Get()->GetWindow()->GetHeight();
        m_Framebuffer = Framebuffer::Create(
            { static_cast<int32_t>(m_WindowWidth), static_cast<int32_t>(m_WindowHeight) });
        m_PostProcessingBuffer = Framebuffer::Create(
            { static_cast<int32_t>(m_WindowWidth), static_cast<int32_t>(m_WindowHeight) });
        m_ShadowBuffer = Framebuffer::Create(
            { 2048, 2048 });
    }

    void EditorLayer::OnDetach()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnDetach();

        Renderer2D::Shutdown();
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        LV_PROFILE_FUNCTION();

        m_AccumulateTime += static_cast<float>(ts);

        m_MainScene->UpdateCameraTrans();
        if (m_SceneCameraController->IsActive() && m_ViewportFocused)
        {
            m_SceneCameraController->OnUpdate(ts);   
        }
        m_MainScene->GetPrimaryCamera(m_PrimaryCamera, m_SceneCamera);

        if (auto const camera = m_PrimaryCamera.lock())
        {
            auto vpMat = glm::mat4(1.f);
#undef near
#undef far
        {
            m_ShadowBuffer->Bind();
            RenderCommand::SwapBuffer(DEPTH_BUFFER);
            Renderer::ResizeViewport(2048, 2048);
            auto constexpr near = 1.f;
            auto constexpr far = 750.f;
            auto const projMat = glm::ortho(-100.f, 100.f, -100.f, 100.f, near, far);
            auto const viewMat = lookAt(
                    glm::vec3(2.f, 10.f, 3.f),
                    glm::vec3(0.f, 0.f, 0.f),
                    glm::vec3(0.f, 1.f, 0.f)
                );
            vpMat = projMat * viewMat;
            m_ShaderLibrary->Get("Shadow")->Bind();
            m_ShaderLibrary->Get("Shadow")->SetUniformMatrix4fv("u_VPMatrix", 1, false, value_ptr(vpMat));

            auto const meshes = m_MainScene->GetWorld()->view<StaticMeshComponent, TransformComponent, RenderableComponent>(entt::exclude<LightSourceComponent>);
            for (auto&& [entity, mesh, trans] : meshes.each())
            {
                m_ShaderLibrary->Get("Shadow")->SetUniformMatrix4fv("u_MMatrix",
                    1, false, value_ptr(trans.GetTransMat()));
                mesh.VAO->Bind();
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        
            m_ShadowBuffer->Unbind();
        }
#define far
#define near
        
            {
                m_Framebuffer->Bind();
                RenderCommand::SwapColor({ 0.01f, 0.01f, 0.1f, 1.f });
                RenderCommand::SwapBuffer();
                Renderer::ResizeViewport(m_WindowWidth, m_WindowHeight);
                Renderer2D::ResetStats();
                    
                // Renderer2D::BeginScene(m_OrthoCameraController->GetCamera());
                //
                // Renderer2D::DrawQuad(
                //     { 0.f, 0.f },
                //     { 0.5f, 0.5f },
                //     m_Texture
                // );
                //
                // Renderer2D::EndScene();
                    
                Renderer::BeginScene(m_SceneCameraController->GetCamera());
                auto const PointLight = m_MainScene->GetEntity("PointLight");
                auto const lightColor = PointLight->GetComponent<ColorComponent>().Color;
                auto const lightVAO = PointLight->GetComponent<StaticMeshComponent>().VAO;
                auto const lightTrans = PointLight->GetComponent<TransformComponent>().TransformMatrix *
                    PointLight->GetComponent<ScaleComponent>().ScaleMatrix;
                auto const lightShader = m_ShaderLibrary->Get("FlatColor");
                lightShader->Bind();
                lightShader->SetUniform4f("u_Color", lightColor.r, lightColor.g, lightColor.b, lightColor.a);
                Renderer::Submit(lightVAO, lightShader, lightTrans);
                Renderer::EndScene();
                    
                // Renderer2D::BeginScene(m_OrthoCameraController->GetCamera());
                // Renderer2D::DrawQuad(
                //     { -0.5f, 0.43f, 0.f },
                //     { 0.6f, 0.05f },
                //     { 1.f, 1.f, 1.f, 1.f }
                // );
                // Renderer2D::EndScene();
                    
                auto const SpotLight = m_MainScene->GetEntity("SpotLight");
                SpotLight->GetComponent<TransformComponent>().Position = camera->GetExtrinsicProps().Position;
                SpotLight->GetComponent<TransformComponent>().Rotation = camera->GetExtrinsicProps().Orient;
                m_MainScene->OnRender(m_PrimaryCamera.lock(), m_ShadowBuffer, vpMat);
                m_Framebuffer->Unbind();
            }
            
            {
                m_PostProcessingBuffer->Bind();
                RenderCommand::SwapBuffer();
                Renderer2D::PostProcessing(m_ShaderLibrary->Get("PostProcessing"), m_Framebuffer);
                m_PostProcessingBuffer->Unbind();
            }
        }
        
    }

    void EditorLayer::OnEvent(Event* e)
    {
        Layer::OnEvent(e);

        if (m_SceneCameraController->IsActive())
        {
            m_SceneCameraController->OnEvent(e);
        }
        auto dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_EVENT(EditorLayer::OnWindowResized));
    }

    void EditorLayer::OnGuiRender()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnGuiRender();
        
        ImGui::SetCurrentContext(ImGuiLayer::GetCurrentContext()); // DLL doesn't share the same memory heaps
        
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        
        static float f = 0.0f;
        static int counter = 0;
        m_ViewportFocused = true;
        
        {
            ImGui::Begin("Monitor");
            
            ImGui::Text("Draw Call Count: %d", Renderer2D::GetStats().GetDrawCallCount());
            ImGui::Text("Quad Count: %d", Renderer2D::GetStats().GetQuadCount());
        
            auto const& io = ImGui::GetIO();
            ImGui::Text("Frame Rate: %.3f", io.Framerate);
        
            ImGui::End();
        }
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });
        {
            ImGui::Begin("Level");                          // Create a window called "Hello, world!" and append into it.
        
            m_ViewportFocused &= ImGui::IsWindowFocused();
            m_ViewportFocused &= ImGui::IsWindowHovered();
            Application::Get()->GetImGuiLayer()->BlockEvent(!m_ViewportFocused);
            
            auto viewportSize = ImVec2ToGLMVec2();
            viewportSize.Im = ImGui::GetContentRegionAvail();
            if (m_FramebufferSize != viewportSize.GLM)
            {
                m_Framebuffer->Resize(viewportSize.GLM);
                m_PostProcessingBuffer->Resize(viewportSize.GLM);
                m_FramebufferSize = viewportSize.GLM;
            }
            ImGui::Image(reinterpret_cast<void*>(m_Framebuffer->GetTexture()), viewportSize.Im,
                { 0, 1 }, { 1, 0 });
        
            ImGui::End();
        }
        ImGui::PopStyleVar();

        m_SceneEntitiesPanel->OnGuiRender();
    }

    bool EditorLayer::OnWindowResized(WindowResizeEvent* e)
    {
        m_WindowWidth = e->GetWidth();
        m_WindowHeight = e->GetHeight();
        Renderer::ResizeViewport(m_WindowWidth, m_WindowHeight);
        return false;
    }
}
