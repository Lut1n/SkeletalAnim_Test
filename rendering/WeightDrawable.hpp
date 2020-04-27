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

    struct Line
    {
        Vec2 p1, p2;
        int jointId;
        float weight;
    };

    bool displayGrid = true;
    bool displayWeight = true;

    WeightDrawable();

    void setup(const sf::VertexArray& vertices, const std::vector<Joint*>& joints);

    void setShaderParameters();

    static sf::Shader s_shader;
    static sf::Shader s_shaderWeight;
    static bool s_assetsLoaded;

    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Joint*> m_joints;
    std::vector<sf::Glsl::Mat4> m_matrices;
    // std::vector<Line> m_lines;

    mutable sf::VertexArray m_edgeShape;
    mutable sf::VertexArray m_lineShape;
};

#endif // WEIGHT_RENDERER_HPP
