#include "Joint.hpp"

// --------------------------------------------------------------------------
Joint::Joint(sf::Transform initPose)
    : m_initPose(initPose)
    , m_pose(initPose)
{
}

// --------------------------------------------------------------------------
Joint::~Joint()
{
}

// --------------------------------------------------------------------------
void Joint::updateTransform()
{
    m_transform = sf::Transform::Identity;
    
    Joint* curr = this;
    while(curr)
    {
        m_transform = curr->m_pose * m_transform;
        curr = dynamic_cast<Joint*>(curr->m_parent);
    }
}

// --------------------------------------------------------------------------
void Joint::computeInitTransform()
{
    sf::Transform initialTransform = sf::Transform::Identity;

    Joint* curr = this;
    while(curr)
    {
        initialTransform = curr->m_initPose * initialTransform;
        curr = dynamic_cast<Joint*>(curr->m_parent);
    }

    m_initTransform = initialTransform;
    m_inverseInitTransform = initialTransform.getInverse();
}

// --------------------------------------------------------------------------
Vec2 Joint::tail()
{
    Vec2 pt = m_initTransform * Vec2(0.0,0.0);
    return pt;
}

// --------------------------------------------------------------------------
Vec2 Joint::head()
{
    Vec2 pt = m_initTransform * Vec2(0.0,0.0);
    return pt;
}

// --------------------------------------------------------------------------
float Joint::distanceFrom(const Vec2& pt)
{
    return 0.0;
}
