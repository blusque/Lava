﻿#include "lvpch.h"
#include "ImGuiLayer.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "imgui_internal.h"
#include "Lava/Core/Application.h"
#include "Lava/Events/KeyboardEvent.h"

namespace Lava
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGui Layer")
    {
    }

    void ImGuiLayer::OnAttach()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnAttach();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        auto& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        auto const window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnDetach();
        
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnGuiRender()
    {
        LV_PROFILE_FUNCTION();
        
        Layer::OnGuiRender();
    }

    void ImGuiLayer::OnEvent(Event* e)
    {
        Layer::OnEvent(e);

        if (m_BlockEvent)
        {
            auto const& io = ImGui::GetIO();
            e->Handled() |= e->IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
            e->Handled() |= e->IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
        }
    }

    void ImGuiLayer::OnBegin() const
    {
        LV_PROFILE_FUNCTION();
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::OnEnd() const
    {
        LV_PROFILE_FUNCTION();
        
        auto& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(Application::Get()->GetWindow()->GetWidth()),
            static_cast<float>(Application::Get()->GetWindow()->GetHeight()));
        
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::BlockEvent(bool block)
    {
        m_BlockEvent = block;
    }


    ImGuiContext* ImGuiLayer::GetCurrentContext()
    {
        return ImGui::GetCurrentContext();
    }
}
