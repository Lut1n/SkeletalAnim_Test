#include "Animator.hpp"
#include <cmath>


float computeWindAt(const Vec2& uv, float ellapsed)
{
    float b0 = std::sin(uv.x + ellapsed * 5.0);
    float b1 = std::sin(uv.x + ellapsed * 10.0);
    float b2 = std::sin(uv.x + ellapsed * 15.0);
    return b0*0.5 + b1*0.3 + b2*0.2;
}


Animator::Animator(int jointCount, float jointLength)
{
    sf::Transform trans; trans.translate( sf::Vector2f(0.f,-jointLength) );
    m_joints.resize(jointCount,nullptr);
    m_joints[0] = new Joint(trans,sf::Transform::Identity);
    for(int i=1;i<jointCount;++i)
    {
        m_joints[i] = new Joint(trans,sf::Transform::Identity);
        m_joints[i-1]->addChild( m_joints[i] );
    }
}

void Animator::animate(const Vec2& scene_pos, float ellapsed_ms)
{
    const float SPEED_FACTOR = 0.5;
    const float MAX_DEG = 10.0;

    for(auto& joint:m_joints)
    {
        float t = computeWindAt(scene_pos, ellapsed_ms * SPEED_FACTOR);
        sf::Transform rot; rot.rotate(t * MAX_DEG);
        rot.combine(joint->m_localInitTransform);
        joint->m_localTransform = rot;
    }
    for(auto& joint:m_joints) joint->updateTransform();
    
}
