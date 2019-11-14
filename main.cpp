
#include <SFML/Graphics.hpp>

#include <cmath>

#include "math_vector.hpp"
#include "JoinRenderer.hpp"
#include "Animator.hpp"
#include "SkinRenderer.hpp"
#include "WindRenderer.hpp"

struct AnimatedTree
{
    static int s_mode;

    Animator m_animator;
    Skin m_skin;
    JoinRenderer m_joinRenderer;
    Vec2 m_position;

    AnimatedTree(const Vec2& position, int joinCount = BONE_COUNT, float joinLength = BONE_LENGTH)
    {
        m_position = position;
        m_animator = Animator(joinCount,joinLength);
        m_skin.setPosition( position );
        m_joinRenderer.setPosition( position );

    }

    void update(float ellapsed_time)
    {
        m_animator.animate(Vec2(m_position.x/640.0,0.f), ellapsed_time);
    }

    void draw(sf::RenderTarget& renderTarget)
    {
        m_skin.setJoins(m_animator.m_joins);
        m_joinRenderer.setJoins(m_animator.m_joins);
        if(s_mode == 0 || s_mode == 1)
            renderTarget.draw(m_skin);
        if(s_mode == 0 || s_mode == 2)
            renderTarget.draw(m_joinRenderer);
    }
};

int AnimatedTree::s_mode = 0;

int main(int argc, char* argv[])
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 360), "Skeletal-Test", sf::Style::Titlebar | sf::Style::Close);

    WindRenderer wind;

    std::vector<AnimatedTree> trees;
    trees.push_back( AnimatedTree(Vec2(160.f,360.f)) );
    trees.push_back( AnimatedTree(Vec2(320.f,360.f), 4, 70.f) );
    trees.push_back( AnimatedTree(Vec2(480.f,360.f),10,25.f) );

    sf::Clock clock;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if(++AnimatedTree::s_mode>=3)AnimatedTree::s_mode=0;
            }
        }

        // update time
        sf::Time elapsed = clock.getElapsedTime();
        float ellapsed_s = elapsed.asMilliseconds() * 1e-3;

        // update animators
        wind.update(ellapsed_s);
        for(auto& t : trees) t.update(ellapsed_s);

        // Draw
        window.clear();
        window.draw(wind);
        for(auto& t : trees) t.draw(window);
        window.display();
    }

    return 0;
}
