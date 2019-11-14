#include "JoinRenderer.hpp"
#include "math_vector.hpp"
#include <cmath>

JoinRenderer::JoinRenderer()
{
    sf::VertexArray vertices(sf::Triangles, 3);
    vertices[0].position = sf::Vector2f(-5.f,0.f);
    vertices[1].position = sf::Vector2f(0.f, -10.f);
    vertices[2].position = sf::Vector2f(5.f, 0.f);
    
    vertices[0].color = sf::Color(0.f,0.f,128.f, 128.f);
    vertices[1].color = sf::Color(255.f,255.f,255.f, 128.f);
    vertices[2].color = sf::Color(0.f,0.f,128.f, 128.f);
    
    m_vertices = vertices;
}

void JoinRenderer::setJoins(std::vector<Join*>& joins)
{
    m_joins = joins;
}

void JoinRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& join:m_joins)
    {
        Vec2 curr_point = join->m_localTransform * Vec2(0.f,0.f);
        
        m_vertices[1].position = sf::Vector2f(0.f, -len(curr_point));
        sf::Transform rot; rot.rotate( std::atan2( curr_point.x,-curr_point.y )*180.f/3.14f );
        
        sf::Transform parent_tfrm;
        if(join->m_parent) parent_tfrm = dynamic_cast<Join*>(join->m_parent)->m_transform;

        states.transform = getTransform() * parent_tfrm * rot;
        target.draw(m_vertices, states);
    }
}
