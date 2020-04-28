#ifndef JOINT_RENDERER_H
#define JOINT_RENDERER_H

#include "../rigging/Joint.hpp"

// --------------------------------------------------------------------------
class JointDrawable
    : public sf::Drawable
    , public sf::Transformable
{
public:
    JointDrawable();
    
    // set joints to draw
    void setJoints(std::vector<Joint*>& joints);

protected:
    // sfml draw override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<Joint*> m_joints;       // joint list
    mutable sf::VertexArray m_vertices; // vertices array used for drawing
};

#endif // JOINT_RENDERER_H
