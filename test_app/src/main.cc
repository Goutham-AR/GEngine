#include <iostream>

#include <Window.hh>
#include <geMath.hh>
#include <Shader.hh>
#include <VertexArray.hh>
#include <VertexBuffer.hh>
#include <IndexBuffer.hh>
#include <Renderable2D.hh>
#include <Renderer2D.hh>
#include <Simple2DRenderer.hh>

using namespace GE::core;
using namespace GE::math;

int main()
{
    Window window{WindowProps{960, 540, "hello"}};

    Shader shader{"assets/vertex.glsl", "assets/fragment.glsl"};
    shader.bind();
    auto ortho = mat4::ortho(0.0f, 15.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    auto color = vec4{1.0f, 1.0f, 0.0f, 1.0f};
    shader.setUniform("projMat", ortho);
    shader.setUniform("colorUniform", color);
    shader.setUniform("modelMat", mat4::trans(vec3{4, 3, 0}));
    shader.setUniform("lightPos", vec2{4.0f, 1.5f});

    Renderable2D sprite1{vec3{5, 5, 0}, vec2{4, 4}, vec4{1, 0, 1, 1}, shader};
    Renderable2D sprite2{vec3{1, 1, 0}, vec2{6, 6}, vec4{0, 1, 1, 1}, shader};

    Simple2DRenderer renderer;

    while (!window.is_closed())
    {

        window.clear();

        auto x = window.get_mouse_x();
        auto y = window.get_mouse_y();

        shader.setUniform(
            "lightPos",
            vec2{
                static_cast<float>(x * 16.0f / 960.0f),
                static_cast<float>(9.0f - y * 9.0f / 540.0f)});

        renderer.attach(&sprite1);
        renderer.attach(&sprite2);
        renderer.render();

        window.update();
    }
}
