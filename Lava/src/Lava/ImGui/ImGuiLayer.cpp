#include "lvpch.h"
#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "Lava/Application.h"
#include "Platform/OpenGL/ImGuiOpenGL.h"

namespace Lava
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGui Layer")
    {
    }

    void ImGuiLayer::OnAttach()
    {
        Layer::OnAttach();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        // ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);
    }

    void ImGuiLayer::OnDetach()
    {
        Layer::OnDetach();
    }

    void ImGuiLayer::OnUpdate()
    {
        Layer::OnUpdate();

        auto& io = ImGui::GetIO();
        auto const winWidth = static_cast<float>(Application::Get()->GetWindow()->GetWidth());
        auto const winHeight = static_cast<float>(Application::Get()->GetWindow()->GetHeight());
        LV_CORE_INFO("winWidth: {0}, winHeight: {1}\n", winWidth, winHeight);
        LV_CORE_ASSERT((winWidth >= 0.0f && winHeight >= 0.0f), "winWidth < 0.0f as {0}, winHeight < 0.0f as {1}\n", winWidth, winHeight)
        io.DisplaySize = ImVec2(winWidth, winHeight);

        auto const time = static_cast<float>(glfwGetTime());
        io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        // {
        //     static float f = 0.0f;
        //     static int counter = 0;
        //
        //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        //
        //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //     // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //     // ImGui::Checkbox("Another Window", &show_another_window);
        //
        //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //     // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
        //
        //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //         counter++;
        //     ImGui::SameLine();
        //     ImGui::Text("counter = %d", counter);
        //
        //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        //     ImGui::End();
        // }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event* e)
    {
        Layer::OnEvent(e);
    }
}
