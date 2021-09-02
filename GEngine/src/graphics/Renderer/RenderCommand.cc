#include "RenderCommand.hh"

#include "../GL/GLRendererAPI.hh"

namespace GE
{

RendererAPI* RenderCommand::s_rendererAPI = new GLRendererAPI{};

}