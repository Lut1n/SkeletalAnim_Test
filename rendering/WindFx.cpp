#include "WindFx.hpp"
#include "../maths/math_vector.hpp"
#include "WindFx_Glsl.hpp"

WindFx::WindFx()
{
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = Vec2(0.f,0.f);
    quad[1].position = Vec2(640.f,0.f);
    quad[2].position = Vec2(640.f,360.f);
    quad[3].position = Vec2(0.f,360.f);
    quad[0].texCoords = Vec2(0.f,0.f);
    quad[1].texCoords = Vec2(1.f,0.f);
    quad[2].texCoords = Vec2(1.f,1.f);
    quad[3].texCoords = Vec2(0.f,1.f);
    m_rectShape = quad;
    
    m_shader.loadFromMemory(windFx_Glsl, sf::Shader::Fragment);
    m_background.loadFromFile("./data/background.png");
}

WindFx::~WindFx()
{
}

void WindFx::update(float ellapsed_s)
{
    m_shader.setUniform("u_ellapsed_s",ellapsed_s);
}

void WindFx::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.shader = &m_shader;
    states.texture = &m_background;
    target.draw(m_rectShape, states);
}
