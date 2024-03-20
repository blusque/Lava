#include "Level.h"

#include "imgui.h"
#include "Pillar.h"
#include "Random.h"
#include "Lava/Renderer/RenderCommand.h"
#include "Lava/Renderer/Renderer.h"
#include "Lava/Renderer/Renderer2D.h"

Level::Level()
    : m_Player(new Player)
    , m_Camera(Lava::Camera::Create({ 1080.f, 1920.f / 1080.f, 1.f }))
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

    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x,  700.f }, { 1920.f, 540.f },
        m_BackGroundColor);
    
    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x,  -700.f }, { 1920.f, 540.f },
        m_BackGroundColor);

    UpdatePillar();
    for (auto&& pillar : m_Pillars)
    {
        Lava::Renderer2D::DrawRotateQuad(
            pillar->GetUpPillarPosition(),
            glm::radians(180.f),
            pillar->GetScale(),
            pillar->GetTexture(),
            1.f, m_BackGroundColor);
        // pillar->GetUpCollision()->Show(pillar->GetUpPillarPosition(), 0.f);
        Lava::Renderer2D::DrawQuad(
            pillar->GetDownPillarPosition(),
            pillar->GetScale(),
            pillar->GetTexture(),
            1.f, m_BackGroundColor);
        // pillar->GetDownCollision()->Show(pillar->GetDownPillarPosition(), 0.f);
    }
    
    Lava::Renderer2D::DrawRotateQuad(m_Player->GetPosition(), glm::radians(m_Player->GetRotation()),
        m_Player->GetScale(), m_Player->GetTexture());

    auto const particles = m_Player->GetParticleSystem()->GetParticlePool();
    for (auto&& particle : particles)
    {
        if (particle.IsAlive)
        {
            Lava::Renderer2D::DrawRotateQuad(
            particle.Position,
            glm::radians(particle.Rotation),
            particle.Size,
            particle.Color);
        }
    }

    // m_Player->GetCollision()->Show(m_Player->GetPosition(), m_Player->GetRotation());

    m_Dead = isCollided();
    
    Lava::Renderer2D::EndScene();

    // LV_TRACE("Player Position: {0}, {1}; Rotation: {2}; ts: {3}", m_Player->GetPosition().x, m_Player->GetPosition().y,
    //     m_Player->GetRotation(), ts);
    if (!m_Dead)
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
        ImGui::ColorEdit3("BackGroundColor", &m_BackGroundColor[0]);
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
        
    posUp.x = m_DistX * static_cast<float>(index) + m_DistX * 3 + 1;
    posDown.x = m_DistX * static_cast<float>(index) + m_DistX * 3;

    auto const base = Random::Rand(-100.f, 100.f);
    auto const gap = Random::Rand(300.f, 340.f);
    posUp.y = base + gap;
    posDown.y = base - gap;

    return Lava::CreateRef<Pillar>(posUp, posDown);
}

void Level::UpdatePillar()
{
    auto const now = m_PillarIndex % m_PillarNum;
    auto const pillar = m_Pillars[now];
    
    if (m_Player->GetPosition().x - pillar->GetUpPillarPosition().x > 1200.f)
    {
        m_Pillars[now] = CreatePillar(m_PillarIndex);
        m_PillarIndex++;
    }
}

bool Level::isCollided()
{
    return std::any_of(m_Pillars.begin(), m_Pillars.end(), [&](const Lava::Ref<Pillar>& pillar)
    {
        return (
                DetectCollision(m_Player->GetCollision(), pillar->GetUpCollision(),
                m_Player->GetPosition(), m_Player->GetRotation(),
                pillar->GetUpPillarPosition(), 0.f) ||
                DetectCollision(m_Player->GetCollision(), pillar->GetDownCollision(),
                m_Player->GetPosition(), m_Player->GetRotation(),
                pillar->GetDownPillarPosition(), 0.f)
            );
    });
}
