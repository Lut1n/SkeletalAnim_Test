#ifndef WIND_FX_HPP
#define WIND_FX_HPP

#include <SFML/Graphics.hpp>

// --------------------------------------------------------------------------
class WindFx
    : public sf::Drawable
    , public sf::Transformable
{
    public:

    WindFx();
    virtual ~WindFx();
    
    void update(float ellapsed_s);

    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    mutable sf::VertexArray m_rectShape;
    sf::Shader m_shader;
    sf::Texture m_background;
};

#endif // WIND_RENDERER_HPP
