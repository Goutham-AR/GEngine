#pragma once

#include <common.hh>
#include "VertexArray.hh"
#include "RenderCommand.hh"
#include "Cameras.hh"
#include "Shader.hh"

namespace GE
{

class GE_PUBLIC Renderer
{

public:
    Renderer() = default;
    virtual ~Renderer() = default;

    static void init();
    static void begin(OrthoGraphicCamera& camera);
    static void end();

    static void submit(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader, const glm::mat4& transformMat = glm::mat4{1.0f});

    static void clear(const glm::vec4& color);

private:
    static OrthoGraphicCamera* s_camera;
};

}