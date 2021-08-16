#pragma once

#include <common.hh>

namespace GE
{

class GE_PUBLIC TimeStep
{
public:
    explicit TimeStep(float time = 0.0f)
        : m_time{time}
    {
    }

    [[nodiscard]] auto getSeconds() const { return m_time; }
    [[nodiscard]] auto getMilliSeconds() const
    {
        return m_time * 1000.0f;
    }

private:
    // in seconds
    float m_time;
};

}