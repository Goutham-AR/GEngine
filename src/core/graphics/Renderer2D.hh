#pragma once

#include "Renderable2D.hh"

namespace GE::core
{

class IRenderer2D
{

public:
    virtual ~IRenderer2D() = default;

    virtual void attach(const Renderable2D* renderable) = 0;
    virtual void render() = 0;
};

}