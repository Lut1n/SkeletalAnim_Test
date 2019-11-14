#include "Join.hpp"

Join::Join(sf::Transform initTransform, sf::Transform transform)
    : m_localInitTransform(initTransform)
    , m_localTransform(transform)
{
}

Join::~Join()
{
}

void Join::updateTransform()
{
    sf::Transform initialTransform = sf::Transform::Identity;
    m_transform = sf::Transform::Identity;
    
    Join* curr = this;
    while(curr)
    {
        m_transform = curr->m_localTransform * m_transform;
        initialTransform = curr->m_localInitTransform * initialTransform;
        curr = dynamic_cast<Join*>(curr->m_parent);
    }
    
    m_initTransform = initialTransform;
    m_inverseInitTransform = initialTransform.getInverse();
}
