#pragma once

#include <common.hh>
#include "../Common/Cameras.hh"
#include "../Common/Texture.hh"
namespace GE
{

struct alignas(64) Quad
{

    glm::vec3 Pos;
    glm::vec2 Size = {1.0f, 1.0f};
    Color Color = {1.0f, 1.0f, 1.0f, 1.0f};
    Sptr<Texture2D> Texture = Texture2D::createWhiteTexture(1, 1);
    float Rotation = 0.0f;
    float TilingFactor = 1.0f;
};

class GE_PUBLIC Renderer2D
{

public:
    Renderer2D() = delete;
    ~Renderer2D() = delete;

    static void init();
    static void shutdown();
    static void begin(const OrthoGraphicCamera& camera);
    static void end();

    static void flush();

    static void drawQuad(const Quad& quadInfo);
};
}