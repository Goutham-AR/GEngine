#include "Renderer2D.hh"
#include "RenderCommand.hh"
#include "../Common/Shader.hh"
#include "../Common/VertexArray.hh"

namespace GE
{

struct R2DData
{
    Sptr<IShader> quadShader = IShader::create("assets/Shaders/QuadShader.vert", "assets/Shaders/QuadShader.frag");
    Sptr<VertexArray> quadVao = VertexArray::create();
};

static R2DData* rendererData = nullptr;

void Renderer2D::init()
{
    rendererData = new R2DData{};
<<<<<<< HEAD:GEngine/src/graphics/Common/Renderer2D.cc
    std::vector<float>
        vertices2{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
=======
    rendererData->quadShader = IShader::create("assets/Shaders/QuadShader.vert", "assets/Shaders/QuadShader.frag");
    rendererData->quadVao = VertexArray::create();
    rendererData->whiteTexture = Texture2D::create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    rendererData->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
    std::vector<float> vertices2{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
>>>>>>> b4aad1e3acca5d8867d9e696e8519dd3706e484c:GEngine/src/graphics/Renderer/Renderer2D.cc
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
    rendererData->quadShader->bind();
    rendererData->quadShader->setUniform("u_viewProjMat", camera.getViewProjectionMat());
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