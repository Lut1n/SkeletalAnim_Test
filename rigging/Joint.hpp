#ifndef JOINT_HPP
#define JOINT_HPP

#include "Graph.hpp"
#include <SFML/Graphics.hpp>

struct Joint : public GraphNode
{
    // local transforms
    sf::Transform m_localInitTransform;
    sf::Transform m_localTransform;

    // result transform from the root of the graph
    sf::Transform m_initTransform;
    sf::Transform m_inverseInitTransform;
    sf::Transform m_transform;

    Joint(sf::Transform initTransform, sf::Transform transform);
    virtual ~Joint();

    void updateTransform();
};

#endif // JOINT_HPP
