#include "EditorLayer.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_transform.hpp>

#include "Lava/Component/ColorComponent.h"
#include "Lava/Component/ScaleComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"
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

        m_Cube = Entity::Create();
        m_LightSource = Entity::Create();

        float const cube[] = {
            -0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,

             0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,

             0.5f, -0.5f,  0.5f,  1.f,  0.f,  0.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  1.f,  0.f,  0.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,

            -0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f,  0.5f, -1.f,  0.f,  0.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f,  0.5f, -1.f,  0.f,  0.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            
            -0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            
            -0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, // 0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, // 1.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
             0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, // 1.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, // 0.0f, 1.0f, 1.f, 1.f, 1.f, 1.f,
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

        m_Cube->AddComponent<StaticMeshComponent>(cube, sizeof(cube), indices, sizeof(indices));
        m_Cube->AddComponent<TransformComponent>(
                glm::vec3{ 0.f, 0.f, 0.f },
                glm::vec3{ 0.f, 0.f, 0.f }
            );
        m_Cube->AddComponent<ScaleComponent>(
                glm::vec3 { 1.f, 1.f, 1.f }
            );
        m_Cube->AddComponent<ColorComponent>(glm::vec4{ 1.f, 0.5f, 0.3f, 1.f });

        m_LightSource->AddComponent<StaticMeshComponent>(cube, sizeof(cube), indices, sizeof(indices));
        m_LightSource->AddComponent<TransformComponent>(
                glm::vec3{ 1.5f, 0.5f, 1.5f },
                glm::vec3{ 0.f, 0.f, 0.f }
            );
        m_LightSource->AddComponent<ScaleComponent>(
                glm::vec3 { 0.4f, 0.4f, 0.4f }
            );
        m_LightSource->AddComponent<ColorComponent>(glm::vec4{ 1.f, 1.f, 1.f, 1.f });

        m_ShaderLibrary = CreateRef<ShaderLibrary>();
        auto const lightShader = Shader::Create();
        auto texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/Phong.glsl));
        lightShader->Compile(texShaderProgram);
        m_ShaderLibrary->Add(lightShader);
        auto const flatColorShader = Shader::Create();
        texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/FlatColor.glsl));
        flatColorShader->Compile(texShaderProgram);
        m_ShaderLibrary->Add(flatColorShader);
        
        m_Texture = Texture::Create(ASSETS_PATH(textures/ChernoLogo.png));
        m_WindowWidth = Application::Get()->GetWindow()->GetWidth();
        m_WindowHeight = Application::Get()->GetWindow()->GetHeight();
        m_Framebuffer = Framebuffer::Create(
            { static_cast<int32_t>(m_WindowWidth), static_cast<int32_t>(m_WindowHeight) });
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
        auto& lightPos = m_LightSource->GetComponent<TransformComponent>().Position;
        lightPos.x = 1.5f * cos(m_AccumulateTime);
        lightPos.z = 1.5f * sin(m_AccumulateTime);


        auto& transMatrix = m_LightSource->GetComponent<TransformComponent>().TransformMatrix;
        auto constexpr Identity = glm::mat4(1.f);
        auto const transMat = translate(Identity, lightPos);
        transMatrix = transMat;

        if (m_ViewportFocused)
        {
            m_CameraController->OnUpdate(ts);   
        }

        m_Framebuffer->Bind();
        
        RenderCommand::SwapColor({ 0.2f, 0.2f, 0.2f, 1.f });
        RenderCommand::SwapBuffer();
        
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

        Renderer::BeginScene(m_CameraController->GetCamera());
        auto const cubeVAO = m_Cube->GetComponent<StaticMeshComponent>().VAO;
        auto const cubeTrans = m_Cube->GetComponent<TransformComponent>().TransformMatrix *
            m_Cube->GetComponent<ScaleComponent>().ScaleMatrix;
        auto const cubeShader = m_ShaderLibrary->Get("Phong");
        cubeShader->Bind();
        auto const cubeColor = m_Cube->GetComponent<ColorComponent>().Color;
        auto const lightColor = m_LightSource->GetComponent<ColorComponent>().Color;
        auto const lightPosition = m_LightSource->GetComponent<TransformComponent>().Position;
        cubeShader->SetUniform4f("u_Color", cubeColor.r, cubeColor.g, cubeColor.b, cubeColor.a);
        cubeShader->SetUniform4f("u_LightColor", lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        cubeShader->SetUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
        Renderer::Submit(cubeVAO, cubeShader, cubeTrans);
        auto const lightVAO = m_Cube->GetComponent<StaticMeshComponent>().VAO;
        auto const lightTrans = m_LightSource->GetComponent<TransformComponent>().TransformMatrix *
            m_LightSource->GetComponent<ScaleComponent>().ScaleMatrix;
        auto const lightShader = m_ShaderLibrary->Get("FlatColor");
        lightShader->Bind();
        lightShader->SetUniform4f("u_Color", lightColor.r, lightColor.g, lightColor.b, lightColor.a);
        Renderer::Submit(lightVAO, lightShader, lightTrans);
        Renderer::EndScene();
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(Event* e)
    {
        Layer::OnEvent(e);

        m_CameraController->OnEvent(e);
        m_OrthoCameraController->OnEvent(e);
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
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        
            ImGui::ColorEdit4("Square Color: ", &m_Cube->GetComponent<ColorComponent>().Color[0]);
        
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
        
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
                m_FramebufferSize = viewportSize.GLM;
            }
            ImGui::Image(reinterpret_cast<void*>(m_Framebuffer->GetTexture()), viewportSize.Im,
                { 0, 1 }, { 1, 0 });
        
            ImGui::End();
        }
        ImGui::PopStyleVar();
    }

    bool EditorLayer::OnWindowResized(WindowResizeEvent* e)
    {
        m_WindowWidth = e->GetWidth();
        m_WindowHeight = e->GetHeight();
        Renderer::ResizeViewport(m_WindowWidth, m_WindowHeight);
        return false;
    }
}
