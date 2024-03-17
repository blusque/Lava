#include "GameLayer.h"

GameLayer::GameLayer()
    : m_Level(new Level)
    , m_Camera(Lava::Camera::Create({ 1080.f, 1920.f / 1080.f, 10.f }))
    , m_CameraController(Lava::CameraController::Create(m_Camera))
{
}

GameLayer::~GameLayer() = default;

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    m_Level->OnBegin();
}

void GameLayer::OnUpdate(Lava::Timestep ts)
{
    Layer::OnUpdate(ts);

    m_Level->OnUpdate(ts);
}

void GameLayer::OnGuiRender()
{
    Layer::OnGuiRender();
    
    ImGui::SetCurrentContext(Lava::ImGuiLayer::GetCurrentContext()); // DLL doesn't share the same memory heaps
    m_Level->OnGuiRender();
}

void GameLayer::OnEvent(Lava::Event* e)
{
    Layer::OnEvent(e);

    m_Level->OnEvent(e);
}

void GameLayer::OnDetach()
{
    Layer::OnDetach();
}
