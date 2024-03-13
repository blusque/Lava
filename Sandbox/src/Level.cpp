#include "Level.h"

#include "Lava/Renderer/RenderCommand.h"
#include "Lava/Renderer/Renderer.h"
#include "Lava/Renderer/Renderer2D.h"

Level::Level()
    : m_Player(new Player)
    , m_Camera(Lava::Camera::Create({ 1920.f / 1080.f, 1.f }))
    , m_CameraController(Lava::CameraController::Create(m_Camera))
{
}

void Level::OnBegin()
{
    
}

void Level::OnUpdate(Lava::Timestep ts)
{
    Lava::Renderer::ResizeCamera(m_CameraController->GetWindowWidth(), m_CameraController->GetWindowHeight());
    m_CameraController->GetCamera()->SetViewMatrix(
        { m_Player->GetPosition().x, m_Player->GetPosition().y, 0.f}, 0.f);

    Lava::RenderCommand::SwapColor({ 0.f, 0.f, 0.f, 1.f });
    Lava::RenderCommand::SwapBuffer();

    Lava::Renderer2D::BeginScene(m_CameraController->GetCamera());

    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x,  1.5f }, { 100.f, 1.f }, { 1.f, 1.f, 1.f, 1.f });

    Lava::Renderer2D::DrawQuad({ m_Player->GetPosition().x, -1.5f }, { 100.f, 1.f }, { 1.f, 1.f, 1.f, 1.f });

    Lava::Renderer2D::DrawRotateQuad(m_Player->GetPosition(), m_Player->GetRotation() - glm::radians(90.f),
        m_Player->GetScale(), m_Player->GetTexture());
    
    Lava::Renderer2D::EndScene();

    // LV_TRACE("Player Position: {0}, {1}; Rotation: {2}; ts: {3}", m_Player->GetPosition().x, m_Player->GetPosition().y,
    //     m_Player->GetRotation(), ts);
    m_Player->OnUpdate(ts);
}

void Level::OnGuiRender()
{
}

void Level::OnEvent(Lava::Event* e)
{
    m_Player->OnEvent(e);
}
