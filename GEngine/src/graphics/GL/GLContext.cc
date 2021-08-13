#include "GLContext.hh"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <Logger.hh>

GE::GLContext::GLContext(GLFWwindow* winHandle)
    : m_winHandle{winHandle}
{
    GE_ASSERT(m_winHandle, "ERROR: Window Handle = nullptr");
}

GE::GLContext::~GLContext()
{
}

void GE::GLContext::init()
{
    glfwMakeContextCurrent(m_winHandle);
    auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GE_ASSERT(success, "Failed to Initialize Glad");
    ENGINE_LOG_INFO("Glad Initialization: Success");
    ENGINE_LOG_INFO("OpenGL Infos: ");
    ENGINE_LOG_INFO("\tVendor     : {0}", glGetString(GL_VENDOR));
    ENGINE_LOG_INFO("\tRenderer   : {0}", glGetString(GL_RENDERER));
    ENGINE_LOG_INFO("\tVersion    : {0}", glGetString(GL_VERSION));
}

void GE::GLContext::swapBuffers()
{
    glfwSwapBuffers(m_winHandle);
}
