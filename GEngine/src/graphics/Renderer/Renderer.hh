#pragma once

#include <common.hh>
#include "../Common/VertexArray.hh"
#include "../Common/Cameras.hh"
#include "../Common/Shader.hh"
#include "RenderCommand.hh"

namespace GE
{

class GE_PUBLIC Renderer
{

public:
    Renderer() = default;
    virtual ~Renderer() = default;

    static void init();
    static void onWindowResize(int newWidth, int newHeight);
    static void begin(const OrthoGraphicCamera& camera);
    static void end();

    static void submit(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<IShader>& shader, const glm::mat4& transformMat = glm::mat4{1.0f});

    static void clear(const glm::vec4& color);

private:
    static OrthoGraphicCamera* s_camera;
};

}