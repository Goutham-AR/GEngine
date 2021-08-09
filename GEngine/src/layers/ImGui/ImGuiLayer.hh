#pragma once

#include "common.hh"
#include "../Layer.hh"

namespace GE
{

class GE_PUBLIC ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onEvent(Event& event) override;

private:
    float m_time{};
};

}