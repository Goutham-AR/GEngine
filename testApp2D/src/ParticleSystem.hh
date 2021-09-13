#pragma once

#include <GE.hh>

struct Particle
{
    glm::vec2 pos{};
    glm::vec4 color{};
    glm::vec2 velocity{};
    float life{};
};

class ParticleSystem
{

    static constexpr int s_numParticles = 1000;

public:
    ParticleSystem()
    {
        m_particles.reserve(1000);
    }

    void reset(Particle& p)
    {
        p.pos = {0, 0};
        p.velocity = {1, 2};
        p.color = {1, 0, 0, 1};
        p.life = 1.0f;
    }

    void onUpdate(GE::TimeStep ts)
    {
        for (auto i = 0; i < s_numParticles; i = (i + 1) % s_numParticles)
        {
            Particle& p = m_particles[i];
            p.life -= ts.getSeconds();

            if (p.life > 0.0f)
            {
                p.pos -= p.velocity * ts.getSeconds();
                p.color.a -= ts.getSeconds() * 2.5f;
            }
            else
            {
                reset(p);
            }
        }
    }

    void render(GE::TimeStep ts)
    {

        for (auto i = 0; i < s_numParticles; i = (i + 1) % s_numParticles)
        {
            Particle& p = m_particles[i];
            m_quad.Color = p.color;
            m_quad.Pos = {p.pos, 0};
            GE::Renderer2D::drawQuad(m_quad);
        }
    }

private:
    std::vector<Particle> m_particles;
    GE::Quad m_quad{};
};