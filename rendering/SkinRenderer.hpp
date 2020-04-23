#ifndef SKIN_RENDERER_HPP
#define SKIN_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "../maths/math_vector.hpp"
#include "../rigging/Join.hpp"

class Skin
    : public sf::Drawable
    , public sf::Transformable
{
    public:

    Skin();
    
    void setJoins(std::vector<Join*> joins);

    static sf::Shader s_shader;
    static sf::Texture s_texture;
    static bool s_assetsLoaded;

    private:
    
    void findClosestJoins(Vec2 vertex, int& i1, int& i2, int& i3);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    std::vector<Join*> m_joins;
    std::vector<sf::Glsl::Mat4> m_matrices;
};

#endif // SKIN_RENDERER_HPP
