#include "Renderer2D.hh"
#include "RenderCommand.hh"
#include "../Common/Shader.hh"
#include "../Common/VertexArray.hh"
#include "../Common/UniformBuffer.hh"

#include <array>

namespace GE
{

struct PerFrameData
{
    glm::mat4 ViewProj;
};

struct QuadVertex
{
    glm::vec4 pos;
    Color color;
    glm::vec2 texCoord;
    float texID;
    float tilingFactor;
};

struct R2DData
{
    static constexpr std::uint32_t MAX_QUADS = 10'000;
    static constexpr std::uint32_t MAX_VERTICES = MAX_QUADS * 4;
    static constexpr std::uint32_t MAX_INDICES = MAX_QUADS * 6;
    static constexpr std::uint32_t MAX_TEXTURES = 32;

    std::uint32_t quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;

    Sptr<IShader> quadShader = IShader::create("assets/Shaders/QuadShader.vert", "assets/Shaders/QuadShader.frag");
    Sptr<VertexBuffer> quadVB;
    Sptr<VertexArray> quadVao = VertexArray::create();
    Sptr<UniformBuffer<PerFrameData>> perFrameUniformBuffer = UniformBuffer<PerFrameData>::create(0);

    std::array<Sptr<Texture2D>, MAX_TEXTURES> textureSlots{};
    std::uint32_t textureSlotIndex = 0;

    glm::vec4 quadVertexPositions[4];
};

static R2DData* rendererData = nullptr;

void Renderer2D::init()
{
    rendererData = new R2DData{};

    rendererData->quadVB = VertexBuffer::create(R2DData::MAX_VERTICES * sizeof(QuadVertex));
    {
        BufferLayout layout = {
            {ShaderDataType::Float4, "a_position", false},
            {ShaderDataType::Float4, "a_color", false},
            {ShaderDataType::Float2, "a_texCoord", false},
            {ShaderDataType::Float, "a_texID", false},
            {ShaderDataType::Float, "a_tilingFactor", false},
        };
        rendererData->quadVB->setLayout(layout);
    }
    rendererData->quadVao->addVertexBuffer(rendererData->quadVB);

    rendererData->quadVertexBufferBase = new QuadVertex[R2DData::MAX_VERTICES];

    std::uint32_t offset = 0;
    auto quadIndices = new std::uint32_t[R2DData::MAX_INDICES];
    for (std::uint32_t i = 0; i < R2DData::MAX_INDICES; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }
    auto quadIB = IndexBuffer::create(quadIndices, R2DData::MAX_INDICES);
    rendererData->quadVao->addIndexBuffer(quadIB);
    delete[] quadIndices;

    rendererData->quadVao->bind();

    rendererData->quadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    rendererData->quadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    rendererData->quadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    rendererData->quadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
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

    int samplers[R2DData::MAX_TEXTURES];
    for (int i = 0; i < R2DData::MAX_TEXTURES; ++i)
    {
        samplers[i] = i;
    }

    rendererData->quadShader->bind();
    rendererData->quadShader->setUniform("u_textures", samplers, R2DData::MAX_TEXTURES);
    rendererData->quadIndexCount = 0;
    rendererData->textureSlotIndex = 0;
    rendererData->quadVertexBufferPtr = rendererData->quadVertexBufferBase;
}

void Renderer2D::drawQuad(const Quad& quadInfo)
{

    float textureIndex = -1.0f;
    for (std::uint32_t i = 0; i < rendererData->textureSlotIndex; ++i)
    {
        if (rendererData->textureSlots[i]->getHandle() == quadInfo.Texture->getHandle())
        {
            textureIndex = static_cast<float>(i);
            break;
        }
    }

    if (textureIndex == -1.0f)
    {
        textureIndex = static_cast<float>(rendererData->textureSlotIndex);
        rendererData->textureSlots[rendererData->textureSlotIndex++] = quadInfo.Texture;
    }

    auto transform = glm::translate(glm::mat4{1.0f}, quadInfo.Pos);
    transform = glm::rotate(transform, glm::radians(quadInfo.Rotation), glm::vec3{0, 0, 1});
    transform = glm::scale(transform, {quadInfo.Size.x, quadInfo.Size.y, 1.0f});

    rendererData->quadVertexBufferPtr->pos = transform * rendererData->quadVertexPositions[0];
    rendererData->quadVertexBufferPtr->color = quadInfo.Color;
    rendererData->quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    rendererData->quadVertexBufferPtr->texID = textureIndex;
    rendererData->quadVertexBufferPtr->tilingFactor = quadInfo.TilingFactor;
    rendererData->quadVertexBufferPtr++;

    rendererData->quadVertexBufferPtr->pos = transform * rendererData->quadVertexPositions[1];
    rendererData->quadVertexBufferPtr->color = quadInfo.Color;
    rendererData->quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    rendererData->quadVertexBufferPtr->texID = textureIndex;
    rendererData->quadVertexBufferPtr->tilingFactor = quadInfo.TilingFactor;
    rendererData->quadVertexBufferPtr++;

    rendererData->quadVertexBufferPtr->pos = transform * rendererData->quadVertexPositions[2];
    rendererData->quadVertexBufferPtr->color = quadInfo.Color;
    rendererData->quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    rendererData->quadVertexBufferPtr->texID = textureIndex;
    rendererData->quadVertexBufferPtr->tilingFactor = quadInfo.TilingFactor;
    rendererData->quadVertexBufferPtr++;

    rendererData->quadVertexBufferPtr->pos = transform * rendererData->quadVertexPositions[3];
    rendererData->quadVertexBufferPtr->color = quadInfo.Color;
    rendererData->quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    rendererData->quadVertexBufferPtr->texID = textureIndex;
    rendererData->quadVertexBufferPtr->tilingFactor = quadInfo.TilingFactor;
    rendererData->quadVertexBufferPtr++;

    rendererData->quadIndexCount += 6;
}

void Renderer2D::flush()
{
    for (std::uint32_t i = 0; i < rendererData->textureSlotIndex; ++i)
    {
        rendererData->textureSlots[i]->bind(i);
    }
    RenderCommand::drawIndexed(rendererData->quadVao, rendererData->quadIndexCount);
}

void Renderer2D::end()
{
    auto dataSize = (std::uint8_t*)rendererData->quadVertexBufferPtr - (std::uint8_t*)rendererData->quadVertexBufferBase;
    rendererData->quadVB->setData(rendererData->quadVertexBufferBase, dataSize);
    flush();
}

}