#include "Animator.hpp"
#include <cmath>


float computeWindAt(const Vec2& uv, float ellapsed)
{
    float b0 = std::sin(uv.x + ellapsed * 5.0);
    float b1 = std::sin(uv.x + ellapsed * 10.0);
    float b2 = std::sin(uv.x + ellapsed * 15.0);
    return b0*0.5 + b1*0.3 + b2*0.2;
}


Animator::Animator(int joinCount, float joinLength)
{
    sf::Transform trans; trans.translate( sf::Vector2f(0.f,-joinLength) );
    m_joins.resize(joinCount,nullptr);
    m_joins[0] = new Join(trans,sf::Transform::Identity);
    for(int i=1;i<joinCount;++i)
    {
        m_joins[i] = new Join(trans,sf::Transform::Identity);
        m_joins[i-1]->addChild( m_joins[i] );
    }
}

void Animator::animate(const Vec2& scene_pos, float ellapsed_ms)
{
    const float SPEED_FACTOR = 0.5;
    const float MAX_DEG = 10.0;

    for(auto& join:m_joins)
    {
        float t = computeWindAt(scene_pos, ellapsed_ms * SPEED_FACTOR);
        sf::Transform rot; rot.rotate(t * MAX_DEG);
        rot.combine(join->m_localInitTransform);
        join->m_localTransform = rot;
    }
    for(auto& join:m_joins) join->updateTransform();
    
}
