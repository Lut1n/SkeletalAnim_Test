#ifndef JOINT_HPP
#define JOINT_HPP

#include "Graph.hpp"
#include <SFML/Graphics.hpp>

#include "../maths/math_vector.hpp"

// --------------------------------------------------------------------------
// Define a Joint (Bone) used for animation
class Joint : public GraphNode
{
public:
    Joint(sf::Transform initPose);
    virtual ~Joint();

    // Compute the initial transform on this joint by traversing the backbone from the root
    void computeInitTransform();

    // set the pose transform with polar coordinates vector
    void setPose(const Vec2& polar);

    // Compute the transform on this joint by traversing the backbone from the root
    void updateTransform();

    // Get the local pose as vector
    Vec2 getPoseVec();

    // Get the initial tail position
    Vec2 tail();

    // Get the initial head position
    Vec2 head();

    // compute distance of a point from this joint
    float distanceFrom(const Vec2& pt);

    // compute the closest position along this joint from another point
    Vec2 closestPoint(const Vec2& pt);

    // return Root-to-Joint transform
    sf::Transform root2Joint();

    // return animation transform (from initial joint position to current joint position)
    sf::Transform animTransform();

    // return the parent joint (same as parent() with static_cast)
    Joint* parentJoint() const;

    // return sorted indexes of joint by distance
    static std::map<float,int> findClosest(Vec2 vertex, const std::vector<Joint*>& joints);

protected:
    sf::Transform m_initPose;               // local initial tail to head
    sf::Transform m_pose;                   // local tail to head

    sf::Transform m_initTransform;          // initial root to head
    sf::Transform m_inverseInitTransform;   // initial head to root
    sf::Transform m_transform;              // root to head
};

#endif // JOINT_HPP
