#include <Lava.h>
#include <LavaEntryPoint.h>

#include "GameLayer.h"

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
        LV_PROFILE_FUNCTION();
        
        Application::OnBegin();

        Push(new GameLayer);

        LV_INFO("Alpha: {0}, Str: {1}", m_Alpha, m_Str);
    }

    int m_Alpha { 0 };
    std::string m_Str;
};


void Lava::RegisterApplication()
{
    LV_PROFILE_FUNCTION();
    
    Application::Register<Sandbox>(1, "Hello World!");
}
