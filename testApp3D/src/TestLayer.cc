#include "TestLayer.hh"

TestLayer::TestLayer()
    : Layer{"TestLayer"}
{
}

void TestLayer::onAttach()
{
}
void TestLayer::onDetach()
{
}
void TestLayer::onUpdate(GE::TimeStep& deltaTime)
{
    GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
}
void TestLayer::onEvent(GE::Event& event)
{
}
void TestLayer::onImGuiRender()
{
}