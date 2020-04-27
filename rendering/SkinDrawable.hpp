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
    
    void setJoints(std::vector<Joint*> joints);

    void setShaderParameters();

    static sf::Shader s_shader;
    static sf::Texture s_texture;
    static bool s_assetsLoaded;

    private:
    
    void findClosestJoints(Vec2 vertex, int& i1, int& i2, int& i3);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    std::vector<Joint*> m_joints;
    std::vector<sf::Glsl::Mat4> m_matrices;
};

#endif // SKIN_RENDERER_HPP
