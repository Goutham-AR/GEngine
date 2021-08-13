#pragma once


#include <common.hh>

namespace GE
{

class GE_PUBLIC GraphicsContext
{
public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() = 0;

};




}