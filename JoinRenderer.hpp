#ifndef JOIN_RENDERER_H
#define JOIN_RENDERER_H

#include "Join.hpp"

struct JoinRenderer
    : public sf::Drawable
    , public sf::Transformable
{
    JoinRenderer();
    
    void setJoins(std::vector<Join*>& joins);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    mutable sf::VertexArray m_vertices;
    std::vector<Join*> m_joins;
};

#endif // JOIN_RENDERER_H
