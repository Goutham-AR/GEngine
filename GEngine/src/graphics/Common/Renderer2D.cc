#include "Renderer2D.hh"
#include "Shader.hh"
#include "VertexArray.hh"
#include "RenderCommand.hh"

namespace GE
{

struct R2DData
{
    Sptr<IShader> quadShader;
    Sptr<VertexArray> quadVao;
    Sptr<Texture2D> whiteTexture;
};

static R2DData* rendererData = nullptr;

void Renderer2D::init()
{
    rendererData = new R2DData{};
    rendererData->quadShader = GE::IShader::create("assets/Shaders/texShader.vert", "assets/Shaders/texShader.frag");
    rendererData->quadVao = GE::VertexArray::create();
    rendererData->whiteTexture = Texture2D::create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    rendererData->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
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
    std::vector<std::uint32_t> indices2{0, 1, 2, 2, 3, 0};
    auto ibo = IndexBuffer::create(&indices2[0], indices2.size());
    rendererData->quadVao->addIndexBuffer(ibo);

    rendererData->quadShader->setUniform("u_texture", 0);
}
void Renderer2D::shutdown()
{
    delete rendererData;
}

void Renderer2D::begin(const OrthoGraphicCamera& camera)
{
    rendererData->quadShader->bind();
    rendererData->quadShader->setUniform("u_viewProjMat", camera.getViewProjectionMat());
}
void Renderer2D::end()
{
}
void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Color& color)
{
    auto transform = glm::translate(glm::mat4{1.0f}, position);
    transform = glm::scale(transform, {size.x, size.y, 1.0f});

    rendererData->quadShader->setUniform("u_modelMat", transform);
    rendererData->quadShader->setUniform("u_color", color);
    rendererData->whiteTexture->bind(0);
    rendererData->quadVao->bind();
    RenderCommand::drawIndexed(rendererData->quadVao);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Sptr<Texture2D>& texture)
{
    auto transform = glm::translate(glm::mat4{1.0f}, position);
    transform = glm::scale(transform, {size.x, size.y, 1.0f});

    texture->bind(0);
    rendererData->quadShader->setUniform("u_modelMat", transform);
    rendererData->quadShader->setUniform("u_color", Color{1, 1, 1, 1});
    rendererData->quadVao->bind();
    RenderCommand::drawIndexed(rendererData->quadVao);
    texture->unbind(0);
}
}