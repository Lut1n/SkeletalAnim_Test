#include "Joint.hpp"

Joint::Joint(sf::Transform initTransform, sf::Transform transform)
    : m_localInitTransform(initTransform)
    , m_localTransform(transform)
{
}

Joint::~Joint()
{
}

void Joint::updateTransform()
{
    sf::Transform initialTransform = sf::Transform::Identity;
    m_transform = sf::Transform::Identity;
    
    Joint* curr = this;
    while(curr)
    {
        m_transform = curr->m_localTransform * m_transform;
        initialTransform = curr->m_localInitTransform * initialTransform;
        curr = dynamic_cast<Joint*>(curr->m_parent);
    }
    
    m_initTransform = initialTransform;
    m_inverseInitTransform = initialTransform.getInverse();
}
