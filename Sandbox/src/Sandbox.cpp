#include "Lava.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "imgui.h"
#include "imgui_internal.h"

// glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
// {
//     glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//     glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//     View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//     View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//     glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//     return Projection * View * Model;
// }

class ExampleLayer: public Lava::Layer
{
public:
    ExampleLayer()
        : Layer("Example Layer")
        , m_Camera(Lava::Camera::Create({-3.2f, 3.2f, -1.8f, 1.8f }))
    {
        m_CameraPosition = m_Camera->GetPosition();
        m_CameraRotation = m_Camera->GetRotation();
        float triangle[] = {
            -0.5f, -0.288f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.288f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  0.577f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        float square[] = {
            -0.75f, -0.75f, 0.0f, 0.0f, 0.2f, 0.4f,
             0.75f, -0.75f, 0.0f, 0.0f, 0.2f, 0.4f,
             0.75f,  0.75f, 0.0f, 0.0f, 0.2f, 0.4f,
            -0.75f,  0.75f, 0.0f, 0.0f, 0.2f, 0.4f
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0
        };

        auto const vertexShader = std::string(
            "#version 330\n"
            "layout (location = 0) in vec4 Position;\n"
            "layout (location = 1) in vec3 Color;\n"
            "uniform mat4 u_VPMatrix;\n"
            "uniform mat4 u_MMatrix;\n"
            "out vec3 v_Color;"
            "void main()\n"
            "{\n"
            "\tgl_Position = u_VPMatrix * u_MMatrix * Position;\n"
            "\tv_Color = Color;\n"
            "}\n"
        );

        auto const fragmentShader = std::string(
            "#version 330\n"
            "in vec3 v_Color;\n"
            "layout (location = 0) out vec4 f_Color;"
            "void main()\n"
            "{\n"
            "\tf_Color = vec4(v_Color, 1.0);\n"
            "}\n"
        );
        
        m_Shader = Lava::Shader::Create();
        auto const shaderProgram = Lava::ShaderProgram{vertexShader, fragmentShader};
        m_Shader->Compile(shaderProgram);
        m_Shader->Bind();
        m_TriVAO = Lava::VertexArray::Create();
        
        m_TriVBO = Lava::VertexBuffer::Create(triangle, sizeof(triangle), Lava::BufferUseType::STATIC);
        m_TriVBO->AddLayout(3, Lava::DataType::FLOAT, false);
        m_TriVBO->AddLayout(3, Lava::DataType::FLOAT, false);
        
        m_TriIBO = Lava::IndexBuffer::Create(indices, 3 * sizeof(unsigned), Lava::BufferUseType::STATIC);
        
        m_TriVAO->AddVertexBuffer(m_TriVBO);
        m_TriVAO->SetIndexBuffer(m_TriIBO);
        
        m_SquVAO = Lava::VertexArray::Create();
        
        m_SquVBO = Lava::VertexBuffer::Create(square, sizeof(square), Lava::BufferUseType::STATIC);
        m_SquVBO->AddLayout(3, Lava::DataType::FLOAT, false);
        m_SquVBO->AddLayout(3, Lava::DataType::FLOAT, false);
        
        m_SquIBO = Lava::IndexBuffer::Create(indices, sizeof(indices), Lava::BufferUseType::STATIC);

        m_SquVAO->AddVertexBuffer(m_SquVBO);
        m_SquVAO->SetIndexBuffer(m_SquIBO);
    }
    ~ExampleLayer() override = default;

    void OnUpdate(Lava::Timestep ts) override
    {
        if (Lava::Input::IsKeyPressed(LV_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        else if (Lava::Input::IsKeyPressed(LV_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Lava::Input::IsKeyPressed(LV_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        else if (Lava::Input::IsKeyPressed(LV_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        else if (Lava::Input::IsKeyPressed(LV_KEY_A))
            m_CameraRotation += m_CameraRotateSpeed * ts;
        else if (Lava::Input::IsKeyPressed(LV_KEY_D))
            m_CameraRotation -= m_CameraRotateSpeed * ts;

        m_Camera->SetPosition(m_CameraPosition);
        m_Camera->SetRotation(m_CameraRotation);
        
        Lava::RenderCommand::SwapColor({ 0.f, 0.f, 0.f, 1.f });
        Lava::RenderCommand::SwapBuffer();

        Lava::Renderer::BeginScene(m_Camera);

        // m_Camera->SetPosition({0.5f, 0.5f, 0.f});
        // m_Camera->SetRotation(m_StartZ);
        Lava::Renderer::Submit(m_SquVAO, m_Shader);
        Lava::Renderer::Submit(m_TriVAO, m_Shader);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        Lava::Renderer::EndScene();
        m_StartZ += 1e-2f;
    }

    void OnEvent(Lava::Event* e) override
    {
        Layer::OnEvent(e);
    }

    void OnGuiRender() override
    {
        Layer::OnGuiRender();
        
        ImGui::SetCurrentContext(Lava::ImGuiLayer::GetCurrentContext()); // DLL doesn't share the same memory heaps
        static float f = 0.0f;
        static int counter = 0;
        
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        
        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        
        ImGui::End();
    }

private:
    Lava::VertexBuffer::ptr m_TriVBO;
    Lava::IndexBuffer::ptr m_TriIBO;
    Lava::VertexArray::ptr m_TriVAO;
    Lava::VertexBuffer::ptr m_SquVBO;
    Lava::IndexBuffer::ptr m_SquIBO;
    Lava::VertexArray::ptr m_SquVAO;
    Lava::Shader::ptr m_Shader;
    Lava::Camera::ptr m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraRotation;
    float m_CameraMoveSpeed { 1.f };
    float m_CameraRotateSpeed { 1.f };
    float m_StartZ { 0.f };
};

class Sandbox: public Lava::Application
{
public:
    Sandbox()
    {
        Push(new ExampleLayer);
    }
    ~Sandbox() override = default;
};


Lava::Application* Lava::CreateApplication()
{
    return new Sandbox;
}
