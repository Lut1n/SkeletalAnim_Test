
#include <SFML/Graphics.hpp>

#include <cmath>

#include "maths/math_vector.hpp"
#include "rendering/JointDrawable.hpp"
#include "rigging/Animator.hpp"
#include "rendering/SkinDrawable.hpp"
#include "rendering/WindFx.hpp"

struct AnimatedTree
{
    static int s_mode;

    Animator m_animator;
    SkinDrawable m_skin;
    JointDrawable m_joint;
    Vec2 m_position;

    AnimatedTree(const Vec2& position, int jointCount = BONE_COUNT, float jointLength = BONE_LENGTH)
    {
        m_position = position;
        m_animator = Animator(jointCount,jointLength);
        m_skin.setPosition( position );
        m_joint.setPosition( position );

    }

    void update(float ellapsed_time)
    {
        m_animator.animate(Vec2(m_position.x/640.0,0.f), ellapsed_time);
    }

    void draw(sf::RenderTarget& renderTarget)
    {
        m_skin.setJoints(m_animator.m_joints);
        m_joint.setJoints(m_animator.m_joints);
        if(s_mode == 0 || s_mode == 1)
            renderTarget.draw(m_skin);
        if(s_mode == 0 || s_mode == 2)
            renderTarget.draw(m_joint);
    }
};

int AnimatedTree::s_mode = 0;

int main(int argc, char* argv[])
{
    using ArgLs = std::vector<std::string>; ArgLs args;
    if(argc>1) args = ArgLs(argv+1, argv+argc);

    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 360), "Skeletal-Test", sf::Style::Titlebar | sf::Style::Close);

    WindFx wind;

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
