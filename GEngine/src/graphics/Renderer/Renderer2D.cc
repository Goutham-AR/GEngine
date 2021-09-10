#include "Renderer2D.hh"
#include "RenderCommand.hh"
#include "../Common/Shader.hh"
#include "../Common/VertexArray.hh"
#include "../Common/UniformBuffer.hh"

namespace GE
{

struct PerFrameData
{
    glm::mat4 ViewProj;
};

struct alignas(32) R2DData
{
    Sptr<IShader> quadShader = IShader::create("assets/Shaders/QuadShader.vert", "assets/Shaders/QuadShader.frag");
    Sptr<VertexArray> quadVao = VertexArray::create();
    Sptr<UniformBuffer<PerFrameData>> perFrameUniformBuffer = UniformBuffer<PerFrameData>::create(0);
};

static R2DData* rendererData = nullptr;

void Renderer2D::init()
{
    rendererData = new R2DData{};
    std::vector<float>
        vertices2{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
    auto vbo = VertexBuffer::create(&vertices2[0], sizeof(float) * vertices2.size());
    {
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_position", false},
            {ShaderDataType::Float2, "a_texCoord", false},
        };
        vbo->setLayout(layout);
    }
    rendererData->quadVao->addVertexBuffer(vbo);
    std::vector<std::uint32_t> indices{0, 1, 2, 2, 3, 0};
    auto ibo = IndexBuffer::create(&indices[0], indices.size());
    rendererData->quadVao->addIndexBuffer(ibo);
}
void Renderer2D::shutdown()
{
    delete rendererData;
}

void Renderer2D::begin(const OrthoGraphicCamera& camera)
{
    PerFrameData perFrameData{};
    perFrameData.ViewProj = camera.getViewProjectionMat();

    rendererData->perFrameUniformBuffer->setData(&perFrameData);
    rendererData->quadShader->bind();
    rendererData->quadShader->setUniform("u_texture", 0);
}
void Renderer2D::end()
{
}

void Renderer2D::drawQuad(const Quad& quadInfo)
{

    auto transform = glm::translate(glm::mat4{1.0f}, quadInfo.Pos);
    transform = glm::rotate(transform, glm::radians(quadInfo.Rotation), glm::vec3{0, 0, 1});
    transform = glm::scale(transform, {quadInfo.Size.x, quadInfo.Size.y, 1.0f});

    quadInfo.Texture->bind(0);
    rendererData->quadShader->setUniform("u_modelMat", transform);
    rendererData->quadShader->setUniform("u_color", quadInfo.Color);
    rendererData->quadShader->setUniform("u_tilingFactor", quadInfo.TilingFactor);
    rendererData->quadVao->bind();
    RenderCommand::drawIndexed(rendererData->quadVao);
    quadInfo.Texture->unbind(0);
}

}