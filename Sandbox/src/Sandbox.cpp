#include "Lava.h"

class Sandbox: public Lava::Application
{
public:
    Sandbox() = default;
    ~Sandbox() override = default;
};


Lava::Application* Lava::CreateApplication()
{
    return new Sandbox();
}
