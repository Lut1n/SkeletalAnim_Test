#ifndef WEIGHT_RENDERER_HPP
#define WEIGHT_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "../maths/math_vector.hpp"
#include "../rigging/Joint.hpp"

// --------------------------------------------------------------------------
class WeightDrawable
    : public sf::Drawable
    , public sf::Transformable
{
public:
    WeightDrawable();

    // initialize the drawable with skin vertices and joints
    void setup(const sf::VertexArray& vertices, const std::vector<Joint*>& joints);

    // setup shader parameters for animation (matrices)
    void setShaderParameters();

protected:
    // sfml draw override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<Joint*> m_joints;               // joint used to compute matrices
    std::vector<sf::Glsl::Mat4> m_matrices;     // matrices are sent to animation shader

    sf::VertexArray m_edgeShape;                // vertices for skin edges
    sf::VertexArray m_weightLineShape;          // vertices for weight's line that bound skin vertices to bones

    // static assets
    static sf::Shader s_shader;                 // animation shader for edges
    static sf::Shader s_shaderWeight;           // animation shader for weight's line
    static bool s_assetsLoaded;                 // flag for unique loading
};

#endif // WEIGHT_RENDERER_HPP
