#include <geMain.hh>
#include <GE.hh>

#include "TestLayer.hh"

class TestApp : public GE::App
{
public:
    TestApp()
    {
        pushOverlay(new TestLayer{});
    }
    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
