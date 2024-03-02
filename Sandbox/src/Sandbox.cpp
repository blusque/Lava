#include "Lava.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "imgui.h"
#include "imgui_internal.h"
#include "Lava/Renderer/Texture.h"

#define ASSETS_ROOT "C:/Users/kokut/dev/Lava/Sandbox/assets/"
#define ASSETS_FILE(x) LV_STR(x)
#define ASSETS_PATH(x) LV_CONCAT(ASSETS_ROOT, ASSETS_FILE(x))

class ExampleLayer: public Lava::Layer
{
public:
    ExampleLayer()
        : Layer("Example Layer")
        , m_Camera(Lava::Camera::Create({-3.2f, 3.2f, -1.8f, 1.8f }))
        , m_ShaderLibrary(new Lava::ShaderLibrary)
    {
        m_CameraPosition = m_Camera->GetPosition();
        m_CameraRotation = m_Camera->GetRotation();
        float square[] = {
            -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
             0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
             0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
            -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0
        };
        
        m_FlatColorShader = Lava::Shader::Create();
        auto const shaderProgram = Lava::Shader::ParseShaderProgram(ASSETS_PATH(shaders/FlatColor.glsl));
        m_FlatColorShader->Compile(shaderProgram);
        m_FlatColorShader->Unbind();

        m_TextureShader = Lava::Shader::Create();
        auto const texShaderProgram = Lava::Shader::ParseShaderProgram(ASSETS_PATH(shaders/Texture.glsl));
        m_TextureShader->Compile(texShaderProgram);
        m_TextureShader->Bind();
        m_Texture = Lava::Texture::Create(ASSETS_PATH(textures/ChernoLogo.png));
        // m_Texture = Lava::Texture::Create(ASSETS_PATH(window_with_flowers.jpg));
        m_Texture->Bind();
        m_TextureShader->Unbind();

        m_ShaderLibrary->Add(m_TextureShader);
        m_ShaderLibrary->Add(m_FlatColorShader);
        
        m_SquVAO = Lava::VertexArray::Create();
        
        m_SquVBO = Lava::VertexBuffer::Create(square, sizeof(square), Lava::BufferUseType::STATIC);
        m_SquVBO->AddLayout(3, Lava::DataType::FLOAT, false);
        m_SquVBO->AddLayout(2, Lava::DataType::FLOAT, false);
        
        m_SquIBO = Lava::IndexBuffer::Create(indices, sizeof(indices), Lava::BufferUseType::STATIC);

        m_SquVAO->AddVertexBuffer(m_SquVBO);
        m_SquVAO->SetIndexBuffer(m_SquIBO);

        Lava::Renderer::Init();
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
        auto trans = glm::vec3(0.f, 0.f, 0.f);

        // auto material = Lava::Material(m_Shader);
        // auto mi = Lava::MaterialInstance(material, "u_Color", { 0.2f, 0.3f, 0.8f, 1.0f });
        // m_TriangleMesh->SetMaterial(mi);

        for (int y = -10; y < 10; y++)
        {
            for (int x = -10; x < 10; x++)
            {
                trans.x = x * 0.2f;
                trans.y = y * 0.2f;
                auto transform = translate(glm::mat4(1.f), trans);
                transform = scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
                m_FlatColorShader->Bind();
                m_FlatColorShader->SetUniform3f("u_Color", m_SquColor.r, m_SquColor.g, m_SquColor.b);
                Lava::Renderer::Submit(m_SquVAO, m_FlatColorShader, transform);       
            }
        }

        m_TextureShader->Bind();
        m_TextureShader->SetUniform1i("u_TexSampler", 0);
        Lava::Renderer::Submit(m_SquVAO, m_TextureShader);

        Lava::Renderer::EndScene();
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
        
        ImGui::ColorEdit3("Square Color: ", &m_SquColor[0]);
        
        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        
        ImGui::End();
    }

private:
    Lava::Ref<Lava::VertexBuffer> m_SquVBO;
    Lava::Ref<Lava::IndexBuffer> m_SquIBO;
    Lava::Ref<Lava::VertexArray> m_SquVAO;
    Lava::Ref<Lava::ShaderLibrary> m_ShaderLibrary;
    Lava::Ref<Lava::Shader> m_FlatColorShader;
    Lava::Ref<Lava::Shader> m_TextureShader;
    Lava::Ref<Lava::Texture> m_Texture;
    Lava::Ref<Lava::Camera> m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraRotation;
    float m_CameraMoveSpeed { 1.f };
    float m_CameraRotateSpeed { 1.f };
    glm::vec3 m_SquColor { 0.2f, 0.3f, 0.8f };
};

class Sandbox: public Lava::Application
{
public:
    ~Sandbox() override = default;

private:
    friend Application;
    
    Sandbox() = default;
    Sandbox(int alpha, std::string str) : m_Alpha(alpha), m_Str(std::move(str)) {}

    void OnBegin() override
    {
        Application::OnBegin();

        Push(new ExampleLayer);

        LV_INFO("Alpha: {0}, Str: {1}", m_Alpha, m_Str);
    }

    int m_Alpha { 0 };
    std::string m_Str;
};


void Lava::RegisterApplication()
{
    Application::Register<Sandbox>(1, "Hello World!");
}
