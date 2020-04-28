#ifndef SKIN_RENDERER_HPP
#define SKIN_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "../maths/math_vector.hpp"
#include "../rigging/Joint.hpp"

// --------------------------------------------------------------------------
class SkinDrawable
    : public sf::Drawable
    , public sf::Transformable
{
public:
    SkinDrawable();
    
    // set joints to animate skin
    void setJoints(std::vector<Joint*> joints);

    // setup shader parameters for animation
    void setShaderParameters();

    // get skin vertices
    const sf::VertexArray& getVertices() const;

protected:
    // sfml draw override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<Joint*> m_joints;               // joint list used for computing matrices
    std::vector<sf::Glsl::Mat4> m_matrices;     // matrices sent to shader for animation
    sf::VertexArray m_vertices;                 // skin vertices

    // static assets
    static sf::Shader s_shader;     // shader
    static sf::Texture s_texture;   // texture
    static bool s_assetsLoaded;     // flag for unique loading
};

#endif // SKIN_RENDERER_HPP
