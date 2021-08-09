#include <GE.hh>

class ExampleLayer : public GE::Layer
{
public:
    explicit ExampleLayer(const std::string& name)
        : Layer{name}
    {
    }

    void onUpdate() override
    {
        LOG_INFO("ExampleLayer::onUpdate: {0}, {1}, {2}", m_name, __LINE__, __FILE__);
    }

    void onEvent(GE::Event& event) override
    {
        LOG_TRACE("ExampleLayer::onEvent: {0}, {1}, {2}", m_name, __LINE__, __FILE__);
    }
};

class TestApp : public GE::App
{
public:
    TestApp()
    {
        pushLayer(new ExampleLayer{"exmapleLayer1"});
        pushLayer(new ExampleLayer{"exmapleLayer2"});
        pushOverlay(new ExampleLayer{"exmapleOverlay1"});
    }

    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
