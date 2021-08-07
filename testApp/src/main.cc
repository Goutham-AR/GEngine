#include <GE.hh>

class TestApp : public GE::App
{
public:
    TestApp() = default;

    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
