#ifndef JOIN_HPP
#define JOIN_HPP

#include "Graph.hpp"
#include <SFML/Graphics.hpp>

struct Join : public GraphNode
{
    // local transforms
    sf::Transform m_localInitTransform;
    sf::Transform m_localTransform;

    // result transform from the root of the graph
    sf::Transform m_initTransform;
    sf::Transform m_inverseInitTransform;
    sf::Transform m_transform;

    Join(sf::Transform initTransform, sf::Transform transform);
    virtual ~Join();

    void updateTransform();
};

#endif // JOIN_HPP
