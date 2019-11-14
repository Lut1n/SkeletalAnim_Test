#ifndef WIND_RENDERER_HPP
#define WIND_RENDERER_HPP

#include <SFML/Graphics.hpp>

class WindRenderer
    : public sf::Drawable
    , public sf::Transformable
{
    public:

    WindRenderer();
    virtual ~WindRenderer();
    
    void update(float ellapsed_s);

    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    mutable sf::VertexArray m_rectShape;
    sf::Shader m_shader;
    sf::Texture m_background;
};

#endif // WIND_RENDERER_HPP
