
#include <SFML/Graphics.hpp>

#include "maths/math_vector.hpp"
#include "rendering/JointDrawable.hpp"
#include "rigging/Animator.hpp"
#include "rendering/SkinDrawable.hpp"
#include "rendering/WindFx.hpp"
#include "rendering/WeightDrawable.hpp"

// --------------------------------------------------------------------------
enum DisplayMode
{
    Display_Skin,
    Display_EdgesAndJoints
};

// --------------------------------------------------------------------------
struct AnimatedTree
{
    static DisplayMode s_displayMode;

    Animator m_animator;        // joint animator
    SkinDrawable m_skin;        // main drawable
    JointDrawable m_joint;      // joint drawable for visual debug
    WeightDrawable m_weights;   // edges and weights drawable for visual debug
    Vec2 m_position;

    AnimatedTree(const Vec2& position, int jointCount = BONE_COUNT, float jointLength = BONE_LENGTH)
    {
        m_position = position;
        m_animator = Animator(jointCount,jointLength);
        m_skin.setPosition( position );
        m_skin.setJoints(m_animator.joints());

        m_joint.setPosition( position );
        m_joint.setJoints(m_animator.joints());

        m_weights.setPosition( position );
        m_weights.setup(m_skin.getVertices(), m_animator.joints());
    }

    void update(float elapsed_time)
    {
        float time_oft = m_position.x/640.0 * 0.5;
        m_animator.animate(elapsed_time - time_oft);
    }

    void draw(sf::RenderTarget& renderTarget)
    {
        m_skin.setShaderParameters();
        m_weights.setShaderParameters();

        if(s_displayMode == Display_Skin)
        {
            renderTarget.draw(m_skin);
        }
        else
        {
            renderTarget.draw(m_joint);
            renderTarget.draw(m_weights);
        }
    }
};

// --------------------------------------------------------------------------
DisplayMode AnimatedTree::s_displayMode = Display_Skin;


// --------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    // put arguments in std vector
    using ArgLs = std::vector<std::string>; ArgLs args;
    if(argc>1) args = ArgLs(argv+1, argv+argc);

    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 360), "Skeletal animation", sf::Style::Titlebar | sf::Style::Close);

    // scene elements
    WindFx windBackground;
    std::vector<AnimatedTree> trees;
    trees.push_back( AnimatedTree(Vec2(160.f,360.f), 3, 100.f) );
    trees.push_back( AnimatedTree(Vec2(320.f,360.f), 5, 70.f) );
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
                if(AnimatedTree::s_displayMode == Display_Skin)
                    AnimatedTree::s_displayMode = Display_EdgesAndJoints;
                else
                    AnimatedTree::s_displayMode = Display_Skin;
            }
        }

        // get elapsed time
        float elapsed = clock.getElapsedTime().asSeconds();

        // update animations
        windBackground.update(elapsed);
        for(auto& t : trees) t.update(elapsed);

        // Draw
        if(AnimatedTree::s_displayMode == Display_Skin)
            window.draw(windBackground);
        else
            window.clear(sf::Color::Black);
        for(auto& t : trees) t.draw(window);

        // display
        window.display();
    }

    return 0;
}
