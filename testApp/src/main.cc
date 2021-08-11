#include <GE.hh>

class TestApp : public GE::App
{
public:
    TestApp()
    {
        // pushOverlay(new GE::ImGuiLayer{});
    }
    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
