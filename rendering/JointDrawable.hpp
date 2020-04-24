#ifndef JOINT_RENDERER_H
#define JOINT_RENDERER_H

#include "../rigging/Joint.hpp"

struct JointDrawable
    : public sf::Drawable
    , public sf::Transformable
{
    JointDrawable();
    
    void setJoints(std::vector<Joint*>& joints);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    mutable sf::VertexArray m_vertices;
    std::vector<Joint*> m_joints;
};

#endif // JOINT_RENDERER_H
