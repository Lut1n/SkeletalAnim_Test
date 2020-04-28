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
    
    // Update wind fx animation with elapsed time
    void update(float elapsed_s);

protected:
    // sfml draw override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_rectShape;    // background shape
    sf::Shader m_shader;            // shader for background
    sf::Texture m_background;       // background texture
};

#endif // WIND_RENDERER_HPP
