#pragma once

#include <common.hh>
#include "Cameras.hh"
#include "Texture.hh"
namespace GE
{

class GE_PUBLIC Renderer2D
{

public:
    Renderer2D() = delete;
    ~Renderer2D() = delete;

    static void init();
    static void shutdown();
    static void begin(const OrthoGraphicCamera& camera);
    static void end();

    static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Color& color);
    static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Sptr<Texture2D>& texture);
};
}