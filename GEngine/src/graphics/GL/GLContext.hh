#pragma once

#include <common.hh>
#include "../GraphicsContext.hh"


struct GLFWwindow;

namespace GE
{

class GE_PUBLIC GLContext : public GraphicsContext
{
public:
    GLContext(GLFWwindow* winHandle);
    ~GLContext() override;


    void init() override;
    void swapBuffers() override;


private:
    GLFWwindow* m_winHandle;
};



}