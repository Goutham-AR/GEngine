#pragma once

#include "common.hh"
#include "../Layer.hh"

namespace GE
{

class GE_PUBLIC ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer() override = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(TimeStep& timeStep) override;

    void onImGuiRender() override;

    void begin();
    void end();

private:
    float m_time{};
};

}