#include "Level.h"

#include "imgui.h"
#include "Pillar.h"
#include "Lava/Renderer/RenderCommand.h"
#include "Lava/Renderer/Renderer.h"
#include "Lava/Renderer/Renderer2D.h"

Level::Level()
    : m_Player(new Player)
    , m_Camera(Lava::Camera::Create({ 1920.f / 1080.f, 30.f }))
    , m_CameraController(Lava::CameraController::Create(m_Camera))
{
    m_Pillars.reserve(m_PillarNum);
}

void Level::OnBegin()
{
    while (m_PillarIndex < m_PillarNum)
    {
        m_Pillars.emplace_back(CreatePillar(m_PillarIndex));
        m_PillarIndex++;
    }
}

void Level::OnUpdate(Lava::Timestep ts)
{
    Lava::Renderer::ResizeCamera(m_CameraController->GetWindowWidth(), m_CameraController->GetWindowHeight());
    m_CameraController->GetCamera()->SetViewMatrix(
        { m_Player->GetPosition().x, m_Player->GetPosition().y, 0.f}, 0.f);

    Lava::RenderCommand::SwapColor({ 0.2f, 0.2f, 0.2f, 1.f });
    Lava::RenderCommand::SwapBuffer();

    Lava::Renderer2D::BeginScene(m_CameraController->GetCamera());

    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x,  45.f }, { 160.f, 40.f }, { 1.f, 1.f, 1.f, 1.f });
    
    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x,  -45.f }, { 160.f, 40.f }, { 1.f, 1.f, 1.f, 1.f });

    UpdatePillar();
    for (auto&& pillar : m_Pillars)
    {
        Lava::Renderer2D::DrawRotateQuad(
            pillar->GetUpPillarPosition(),
            glm::radians(180.f),
            pillar->GetScale(),
            pillar->GetTexture());
        Lava::Renderer2D::DrawQuad(
            pillar->GetDownPillarPosition(),
            pillar->GetScale(),
            pillar->GetTexture());
    }
    
    Lava::Renderer2D::DrawRotateQuad(m_Player->GetPosition(), m_Player->GetRotation() - glm::radians(90.f),
        m_Player->GetScale(), m_Player->GetTexture());
    
    Lava::Renderer2D::EndScene();

    // LV_TRACE("Player Position: {0}, {1}; Rotation: {2}; ts: {3}", m_Player->GetPosition().x, m_Player->GetPosition().y,
    //     m_Player->GetRotation(), ts);
    m_Player->OnUpdate(ts);
}

void Level::OnGuiRender()
{
    m_Player->OnGuiRender();

    {
        ImGui::Begin("Pos & Deep & Dist");
        ImGui::SliderFloat("Dist X", &m_DistX, 1.f, 200.f);
        ImGui::SliderFloat("Pos Y", &m_PosY, 1.f, 300.f);
        ImGui::SliderFloat("Deep Z", &m_DeepZ, 0.1f, 1.f);
        ImGui::Text("Pillar Index %d", m_PillarIndex);
        ImGui::End();
    }
}

void Level::OnEvent(Lava::Event* e)
{
    m_Player->OnEvent(e);
}

Lava::Ref<Pillar> Level::CreatePillar(uint32_t index)
{
    auto posUp = glm::vec3(0.f);
    auto posDown = glm::vec3(0.f);
    posUp.z = 0.1f * static_cast<float>(index % m_PillarNum) - 0.5f;
    posDown.z = 0.1f * static_cast<float>(index % m_PillarNum) - 0.5f + m_DeepZ / 2.f;
        
    posUp.x = m_DistX * static_cast<float>(index);
    posDown.x = m_DistX * static_cast<float>(index);
        
    posUp.y = m_PosY;
    posDown.y = -m_PosY;

    return Lava::CreateRef<Pillar>(posUp, posDown);
}

void Level::UpdatePillar()
{
    auto const now = m_PillarIndex % m_PillarNum;
    auto const pillar = m_Pillars[now];
    
    if (m_Player->GetPosition().x - pillar->GetUpPillarPosition().x > 70.f)
    {
        m_Pillars[now] = CreatePillar(m_PillarIndex);
        m_PillarIndex++;
    }
}
