
#include <SFML/Graphics.hpp>

#include "maths/math_vector.hpp"
#include "rendering/JointDrawable.hpp"
#include "rigging/Animator.hpp"
#include "rendering/SkinDrawable.hpp"
#include "rendering/WindFx.hpp"
#include "rendering/WeightDrawable.hpp"

// --------------------------------------------------------------------------
struct AnimatedTree
{
    enum DisplayMode
    {
        Display_None = 0,
        Display_Skin,
        Display_Joint,
        Display_Weight,
        Display_Skin_Joint,
        Display_Weight_Joint,
        Display_Skin_Weight,
        Display_All,

        Display_ModeCount,
    };

    static DisplayMode s_displayMode;

    Animator m_animator;    // joint animator
    SkinDrawable m_skin;    // main drawable
    JointDrawable m_joint;  // joint drawable for visual debug
    WeightDrawable m_weights;
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
        m_weights.setup(m_skin.m_vertices, m_animator.joints());
    }

    void update(float ellapsed_time)
    {
        float time_oft = m_position.x/640.0 * 0.5;
        m_animator.animate(ellapsed_time - time_oft);
    }

    void draw(sf::RenderTarget& renderTarget)
    {
        m_skin.setShaderParameters();
        m_weights.setShaderParameters();

        if(s_displayMode == Display_Skin || s_displayMode == Display_Skin_Joint || s_displayMode == Display_Skin_Weight || s_displayMode == Display_All)
            renderTarget.draw(m_skin);
        if(s_displayMode == Display_Joint || s_displayMode == Display_Skin_Joint || s_displayMode == Display_Weight_Joint || s_displayMode == Display_All)
            renderTarget.draw(m_joint);
        if(s_displayMode == Display_Weight || s_displayMode == Display_Skin_Weight || s_displayMode == Display_Weight_Joint || s_displayMode == Display_All)
            renderTarget.draw(m_weights);
    }
};

AnimatedTree::DisplayMode AnimatedTree::s_displayMode = AnimatedTree::Display_Skin;

int main(int argc, char* argv[])
{
    // put arguments in std vector
    using ArgLs = std::vector<std::string>; ArgLs args;
    if(argc>1) args = ArgLs(argv+1, argv+argc);

    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 360), "Skeletal-Test", sf::Style::Titlebar | sf::Style::Close);

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
                int dm = AnimatedTree::s_displayMode;
                AnimatedTree::s_displayMode = static_cast<AnimatedTree::DisplayMode>(dm+1);
                if(AnimatedTree::s_displayMode >= AnimatedTree::Display_ModeCount)
                    AnimatedTree::s_displayMode = AnimatedTree::Display_Skin;
            }
        }

        // update time
        float elapsed = clock.getElapsedTime().asSeconds();

        // update animators
        windBackground.update(elapsed);
        for(auto& t : trees) t.update(elapsed);

        // Draw
        window.clear();
        window.draw(windBackground);
        for(auto& t : trees) t.draw(window);
        window.display();
    }

    return 0;
}
