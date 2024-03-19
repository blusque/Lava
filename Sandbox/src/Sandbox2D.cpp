#include "Sandbox2D.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_transform.hpp>

#include "Lava/Debug/Instrumentor.h"
#include "Lava/Renderer/Renderer2D.h"

void Sandbox2D::OnAttach()
{
    LV_PROFILE_FUNCTION();
    
    Layer::OnAttach();
    
    m_Texture = Lava::Texture::Create(ASSETS_PATH(textures/ChernoLogo.png));
}

void Sandbox2D::OnDetach()
{
    LV_PROFILE_FUNCTION();
    
    Layer::OnDetach();

    Lava::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Lava::Timestep ts)
{
    LV_PROFILE_FUNCTION();
    
    m_CameraController->OnUpdate(ts);

    Lava::Renderer::ResizeCamera(m_CameraController->GetWindowWidth(),
        m_CameraController->GetWindowHeight());
    
    Lava::RenderCommand::SwapColor({ 0.f, 0.f, 0.f, 1.f });
    Lava::RenderCommand::SwapBuffer();
    
    auto transform = glm::vec3(0.f, 0.f, 0.f);
    Lava::Renderer2D::BeginScene(m_CameraController->GetCamera());

    {
        LV_PROFILE_SCOPE("Draw 100 Quad!");
        for (int y = -10; y < 10; y++)
        {
            for (int x = -10; x < 10; x++)
            {
                transform.x = static_cast<float>(x) * 0.2f;
                transform.y = static_cast<float>(y) * 0.2f;
                if (x % 2 == 0 && y % 2 == 0)
                    Lava::Renderer2D::DrawQuad(transform, { 0.1f, 0.1f }, m_SquColor);
                else
                    Lava::Renderer2D::DrawRotateQuad(transform, glm::radians(45.f), { 0.1f, 0.1f }, m_SquColor);
            }
        }
    }

    // {
    //     LV_PROFILE_SCOPE("Draw texture!");
    //     Lava::Renderer2D::DrawQuad({0.f, 0.f}, {1.f, 1.f}, m_Texture, 10.f);
    // }
        
    Lava::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Lava::Event* e)
{
    Layer::OnEvent(e);

    m_CameraController->OnEvent(e);
}

void Sandbox2D::OnGuiRender()
{
    LV_PROFILE_FUNCTION();
    
    Layer::OnGuiRender();
    
    ImGui::SetCurrentContext(Lava::ImGuiLayer::GetCurrentContext()); // DLL doesn't share the same memory heaps
    static float f = 0.0f;
    static int counter = 0;
    
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    
    ImGui::ColorEdit4("Square Color: ", &m_SquColor[0]);
    
    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    
    ImGui::End();
}
