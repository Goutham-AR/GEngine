#pragma once

#include <common.hh>
#include <events/Event.hh>

#include <string>

namespace GE
{
class GE_PUBLIC Layer
{
public:
    explicit Layer(const std::string& name)
        : m_name{name}
    {
    }
    virtual ~Layer() = default;

    virtual void onAttach(){};
    virtual void onDetach(){};
    virtual void onUpdate(){};
    virtual void onEvent(Event& event){};
    virtual void onImGuiRender(){};

    [[nodiscard]] inline const std::string& getName() const { return m_name; }

protected:
    std::string m_name;
};
}