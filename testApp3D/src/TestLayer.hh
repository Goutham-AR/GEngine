#pragma once

#include <GE.hh>

class TestLayer : public GE::Layer
{
public:
    TestLayer();
    ~TestLayer() override = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(GE::TimeStep& deltaTime) override;
    void onEvent(GE::Event& event) override;
    void onImGuiRender() override;

private:
};