#include "Animator.hpp"
#include <cmath>

// --------------------------------------------------------------------------
float computeWindAt(float ellapsed)
{
    float b0 = std::sin(ellapsed * 5.0);
    float b1 = std::sin(ellapsed * 10.0);
    float b2 = std::sin(ellapsed * 15.0);
    return b0*0.5 + b1*0.3 + b2*0.2;
}

// --------------------------------------------------------------------------
Animator::Animator(int jointCount, float jointLength)
{
    buildSkeleton(jointCount, jointLength);
}

// --------------------------------------------------------------------------
void Animator::buildSkeleton(int count, float length)
{
    // init pose
    sf::Transform initPose; initPose.translate( Vec2(0.f,-length) );

    // build structure
    m_joints.resize(count,nullptr);
    for(int i=0;i<count;++i)
    {
        m_joints[i] = new Joint(initPose);
        if(i>0) m_joints[i-1]->addChild( m_joints[i] );
    }

    // compute init transform for each node
    for(auto& joint : m_joints) joint->computeInitTransform();
}

// --------------------------------------------------------------------------
void Animator::animate(float ellapsed)
{
    const float SPEED_FACTOR = 0.5;
    const float MAX_DEG = 10.0;
    float t = computeWindAt(ellapsed * SPEED_FACTOR);

    // update poses
    for(auto& joint:m_joints)
    {
        joint->m_pose = sf::Transform::Identity;
        joint->m_pose.rotate(t * MAX_DEG);
        joint->m_pose.combine(joint->m_initPose);
    }

    // compute transform
    for(auto& joint:m_joints) joint->updateTransform();
}

// --------------------------------------------------------------------------
std::vector<Joint*>& Animator::joints()
{
    return m_joints;
}
