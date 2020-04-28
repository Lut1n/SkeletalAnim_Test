#include "SkinDrawable.hpp"
#include "vertex_shader.hpp"
#include <cmath>
#include <iostream>

#define VERTEX_COUNT 10
#define SKIN_LEN 300

// --------------------------------------------------------------------------
sf::Shader SkinDrawable::s_shader;
sf::Texture SkinDrawable::s_texture;
bool SkinDrawable::s_assetsLoaded = false;

// --------------------------------------------------------------------------
SkinDrawable::SkinDrawable()
{
    if(s_assetsLoaded == false)
    {
        s_texture.loadFromFile("./data/tree.png");
        s_texture.setSmooth(true);
        s_shader.loadFromMemory(s_riggingVertCode_skin, sf::Shader::Vertex);
        s_assetsLoaded = true;
    }
    
    sf::VertexArray quad(sf::TriangleStrip, VERTEX_COUNT);
    float step = float(VERTEX_COUNT) / 2.f;

    const float W = s_texture.getSize().x;
    const float H = s_texture.getSize().y;
    for(int i=0;i<step;++i)
    {
        quad[i*2].position = Vec2(-SKIN_LEN*0.1f, -i*SKIN_LEN/(step-1));
        quad[i*2+1].position = Vec2(SKIN_LEN*0.1f, -i*SKIN_LEN/(step-1));
        quad[i*2].texCoords = Vec2(0.f, H-i*H/(step-1));
        quad[i*2+1].texCoords = Vec2(W, H-i*H/(step-1));
    }
    m_vertices = quad;

}

// --------------------------------------------------------------------------
void SkinDrawable::setJoints(std::vector<Joint*> joints)
{
    m_joints = joints;
    int boneCount = m_joints.size();
    m_matrices.resize(boneCount, sf::Transform::Identity);

    for(int i=0;i<VERTEX_COUNT;++i)
    {
        const int N = 2;

        std::map<float,int> cj = Joint::findClosest(m_vertices[i].position, m_joints);
        float weights[N] = {0,0};
        int indexes[N] = {0,0};

        // compute weights
        if(cj.size() == 1)
        {
            weights[0] = 1.0;
            indexes[0] = cj.begin()->second;
        }
        else
        {
            float dtt = 0.0;
            auto it = cj.begin();
            for(int k=0;k<N;++k)
            {
                if(it == cj.end()) break;
                dtt += it->first;
                ++it;
            }
            it = cj.begin();
            for(int k=0;k<N;++k)
            {
                if(it == cj.end()) break;
                weights[k] = 1.0 - it->first / dtt;
                indexes[k] = it->second;
                ++it;
            }
        }

        // update color with 2 indexes and 2 weights
        sf::Color c;
        c.r = indexes[0]*255.0/boneCount;
        c.g = indexes[1]*255.0/boneCount;
        c.b = weights[0]*255;
        c.a = weights[1]*255;
        m_vertices[i].color = c;

    }
}

// --------------------------------------------------------------------------
void SkinDrawable::setShaderParameters()
{
    int boneCount = m_joints.size();

    for(int i=0;i<boneCount;++i) {
        m_matrices[i] = m_joints[i]->animTransform();
    }
    s_shader.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shader.setUniform("u_jointCount",float(boneCount));
}

// --------------------------------------------------------------------------
const sf::VertexArray& SkinDrawable::getVertices() const
{
    return m_vertices;
}

// --------------------------------------------------------------------------
void SkinDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    states.shader = &s_shader;
    states.texture = &s_texture;
    
    target.draw(m_vertices, states);
}
