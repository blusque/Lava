#include "lvpch.h"
#include "ImGuiLayer.h"

// temporary
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Lava/Application.h"
#include "Platform/OpenGL/ImGuiOpenGL.h"

namespace Lava
{
    static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key)
    {
        switch (key)
        {
            case GLFW_KEY_TAB: return ImGuiKey_Tab;
            case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
            case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
            case GLFW_KEY_UP: return ImGuiKey_UpArrow;
            case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
            case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
            case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
            case GLFW_KEY_HOME: return ImGuiKey_Home;
            case GLFW_KEY_END: return ImGuiKey_End;
            case GLFW_KEY_INSERT: return ImGuiKey_Insert;
            case GLFW_KEY_DELETE: return ImGuiKey_Delete;
            case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
            case GLFW_KEY_SPACE: return ImGuiKey_Space;
            case GLFW_KEY_ENTER: return ImGuiKey_Enter;
            case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
            case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
            case GLFW_KEY_COMMA: return ImGuiKey_Comma;
            case GLFW_KEY_MINUS: return ImGuiKey_Minus;
            case GLFW_KEY_PERIOD: return ImGuiKey_Period;
            case GLFW_KEY_SLASH: return ImGuiKey_Slash;
            case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
            case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
            case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
            case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
            case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
            case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
            case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
            case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
            case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
            case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
            case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
            case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
            case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
            case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
            case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
            case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
            case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
            case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
            case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
            case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
            case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
            case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
            case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
            case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
            case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
            case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
            case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
            case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
            case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
            case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
            case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
            case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
            case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
            case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
            case GLFW_KEY_MENU: return ImGuiKey_Menu;
            case GLFW_KEY_0: return ImGuiKey_0;
            case GLFW_KEY_1: return ImGuiKey_1;
            case GLFW_KEY_2: return ImGuiKey_2;
            case GLFW_KEY_3: return ImGuiKey_3;
            case GLFW_KEY_4: return ImGuiKey_4;
            case GLFW_KEY_5: return ImGuiKey_5;
            case GLFW_KEY_6: return ImGuiKey_6;
            case GLFW_KEY_7: return ImGuiKey_7;
            case GLFW_KEY_8: return ImGuiKey_8;
            case GLFW_KEY_9: return ImGuiKey_9;
            case GLFW_KEY_A: return ImGuiKey_A;
            case GLFW_KEY_B: return ImGuiKey_B;
            case GLFW_KEY_C: return ImGuiKey_C;
            case GLFW_KEY_D: return ImGuiKey_D;
            case GLFW_KEY_E: return ImGuiKey_E;
            case GLFW_KEY_F: return ImGuiKey_F;
            case GLFW_KEY_G: return ImGuiKey_G;
            case GLFW_KEY_H: return ImGuiKey_H;
            case GLFW_KEY_I: return ImGuiKey_I;
            case GLFW_KEY_J: return ImGuiKey_J;
            case GLFW_KEY_K: return ImGuiKey_K;
            case GLFW_KEY_L: return ImGuiKey_L;
            case GLFW_KEY_M: return ImGuiKey_M;
            case GLFW_KEY_N: return ImGuiKey_N;
            case GLFW_KEY_O: return ImGuiKey_O;
            case GLFW_KEY_P: return ImGuiKey_P;
            case GLFW_KEY_Q: return ImGuiKey_Q;
            case GLFW_KEY_R: return ImGuiKey_R;
            case GLFW_KEY_S: return ImGuiKey_S;
            case GLFW_KEY_T: return ImGuiKey_T;
            case GLFW_KEY_U: return ImGuiKey_U;
            case GLFW_KEY_V: return ImGuiKey_V;
            case GLFW_KEY_W: return ImGuiKey_W;
            case GLFW_KEY_X: return ImGuiKey_X;
            case GLFW_KEY_Y: return ImGuiKey_Y;
            case GLFW_KEY_Z: return ImGuiKey_Z;
            case GLFW_KEY_F1: return ImGuiKey_F1;
            case GLFW_KEY_F2: return ImGuiKey_F2;
            case GLFW_KEY_F3: return ImGuiKey_F3;
            case GLFW_KEY_F4: return ImGuiKey_F4;
            case GLFW_KEY_F5: return ImGuiKey_F5;
            case GLFW_KEY_F6: return ImGuiKey_F6;
            case GLFW_KEY_F7: return ImGuiKey_F7;
            case GLFW_KEY_F8: return ImGuiKey_F8;
            case GLFW_KEY_F9: return ImGuiKey_F9;
            case GLFW_KEY_F10: return ImGuiKey_F10;
            case GLFW_KEY_F11: return ImGuiKey_F11;
            case GLFW_KEY_F12: return ImGuiKey_F12;
            case GLFW_KEY_F13: return ImGuiKey_F13;
            case GLFW_KEY_F14: return ImGuiKey_F14;
            case GLFW_KEY_F15: return ImGuiKey_F15;
            case GLFW_KEY_F16: return ImGuiKey_F16;
            case GLFW_KEY_F17: return ImGuiKey_F17;
            case GLFW_KEY_F18: return ImGuiKey_F18;
            case GLFW_KEY_F19: return ImGuiKey_F19;
            case GLFW_KEY_F20: return ImGuiKey_F20;
            case GLFW_KEY_F21: return ImGuiKey_F21;
            case GLFW_KEY_F22: return ImGuiKey_F22;
            case GLFW_KEY_F23: return ImGuiKey_F23;
            case GLFW_KEY_F24: return ImGuiKey_F24;
            default: return ImGuiKey_None;
        }
    }
    
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
        // LV_CORE_INFO("winWidth: {0}, winHeight: {1}\n", winWidth, winHeight);
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

        auto dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<MouseMoveEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnMouseMoveEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnWindowResizedEvent));
        dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_EVENT(&ImGuiLayer::OnWindowCloseEvent));
    }

    void ImGuiLayer::UpdateKeyModifiers(unsigned mods) const
    {
        auto& io = ImGui::GetIO();
        io.AddKeyEvent(ImGuiMod_Ctrl,  mods == 1);
        io.AddKeyEvent(ImGuiMod_Shift, mods == 2);
        io.AddKeyEvent(ImGuiMod_Alt,   mods == 4);
        io.AddKeyEvent(ImGuiMod_Super, mods == 8);
    }

    bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent* e)
    {
        auto& io = ImGui::GetIO();
        io.AddMousePosEvent(e->GetNewX(), e->GetNewY());
        
        return false;
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent* e)
    {
        UpdateKeyModifiers(e->GetMods());
        
        auto& io = ImGui::GetIO();
        if (e->GetMouseButton() < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(static_cast<int>(e->GetMouseButton()), true);
        
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent* e)
    {
        UpdateKeyModifiers(e->GetMods());
        
        auto& io = ImGui::GetIO();
        if (e->GetMouseButton() < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(static_cast<int>(e->GetMouseButton()), false);
        
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent* e)
    {
        auto& io = ImGui::GetIO();
        io.AddMouseWheelEvent(e->GetOffsetX(), e->GetOffsetY());
        
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent* e)
    {
        UpdateKeyModifiers(e->GetMods());

        auto& io = ImGui::GetIO();
        ImGuiKey const imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(static_cast<int>(e->GetKey()));
        io.AddKeyEvent(imgui_key, true);

        return false;
        // io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent* e)
    {
        UpdateKeyModifiers(e->GetMods());
        
        auto& io = ImGui::GetIO();
        ImGuiKey const imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(static_cast<int>(e->GetKey()));
        io.AddKeyEvent(imgui_key, false);

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent* e)
    {
        auto& io = ImGui::GetIO();
        if (e->GetKey() < 0x10000)
            io.AddInputCharacter(e->GetKey());
        
        return false;
    }

    bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent* e)
    {
        auto& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(e->GetWidth()), static_cast<float>(e->GetHeight()));
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0, 0, e->GetWidth(), e->GetHeight());
        
        return false;
    }

    bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent* e)
    {
        return false;
    }
}
