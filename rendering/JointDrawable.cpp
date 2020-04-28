#include "JointDrawable.hpp"
#include "../maths/math_vector.hpp"
#include <cmath>

// --------------------------------------------------------------------------
JointDrawable::JointDrawable()
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

// --------------------------------------------------------------------------
void JointDrawable::setJoints(std::vector<Joint*>& joints)
{
    m_joints = joints;
}

// --------------------------------------------------------------------------
void JointDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& joint:m_joints)
    {
        Vec2 jointVec = joint->getPoseVec();
        Vec2 polar = cart2polar(jointVec);

        m_vertices[1].position = Vec2(0,-polar.x);
        sf::Transform rot; rot.rotate(polar.y * Rad2Deg + 90.0);
        
        sf::Transform parent_tfrm;
        Joint* parent = joint->parentJoint();
        if(parent) parent_tfrm = parent->root2Joint();

        states.transform = getTransform() * parent_tfrm * rot;
        target.draw(m_vertices, states);
    }
}
