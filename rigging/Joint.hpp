#ifndef JOINT_HPP
#define JOINT_HPP

#include "Graph.hpp"
#include <SFML/Graphics.hpp>

#include "../maths/math_vector.hpp"

// --------------------------------------------------------------------------
// Define a Joint (Bone) used for animation
struct Joint : public GraphNode
{
    // transforms relative to parent
    sf::Transform m_initPose;
    sf::Transform m_pose;

    // result transform in world space
    sf::Transform m_initTransform;
    sf::Transform m_inverseInitTransform;
    sf::Transform m_transform;

    Joint(sf::Transform initPose);
    virtual ~Joint();

    void updateTransform();

    void computeInitTransform();

    Vec2 tail();
    Vec2 head();

    float distanceFrom(const Vec2& pt);
};

#endif // JOINT_HPP
