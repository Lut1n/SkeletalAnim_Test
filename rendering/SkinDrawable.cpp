#include "SkinDrawable.hpp"
#include "vertex_shader.hpp"
#include <cmath>
#include <iostream>

#define VERTEX_COUNT 10
#define SKIN_LEN 300

sf::Shader SkinDrawable::s_shader;
sf::Texture SkinDrawable::s_texture;
bool SkinDrawable::s_assetsLoaded = false;

SkinDrawable::SkinDrawable()
{
    if(s_assetsLoaded == false)
    {
        s_texture.loadFromFile("./data/tree.png");
        s_texture.setSmooth(true);
        s_shader.loadFromMemory(vertCode, sf::Shader::Vertex);
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

void SkinDrawable::setJoints(std::vector<Joint*> joints)
{
    m_joints = joints;
    int boneCount = m_joints.size();

    for(int i=0;i<VERTEX_COUNT;++i)
    {
        int c1,c2,c3;
        // float w1,w2;
        findClosestJoints(m_vertices[i].position,c1,c2,c3);
        m_vertices[i].color = sf::Color(float(c1)*255.0/boneCount,
                                        float(c2)*255.0/boneCount,
                                        float(c3)*255.0/boneCount,255.0);
    }
    
    m_matrices.resize(50, sf::Transform::Identity);
    for(int i=0;i<boneCount;++i) {
        m_matrices[i] = m_joints[i]->m_transform * m_joints[i]->m_inverseInitTransform;
    }
    s_shader.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shader.setUniform("u_jointCount",float(boneCount));
}

void SkinDrawable::findClosestJoints(Vec2 vertex, int& i1, int& i2, int& i3)
{
    std::map<float,int> ordered;
    for(int i=0;i<(int)m_joints.size();++i)
    {
        Vec2 rel = m_joints[i]->m_initTransform * Vec2(0.0,0.0);
        float l = len(rel - vertex);
        ordered[l] = i;
    }
    
    auto it = ordered.begin();
    i1 = it->second; it++;
    i2 = it->second; it++;
    i3 = it->second;
}

void SkinDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    states.shader = &s_shader;
    states.texture = &s_texture;
    
    target.draw(m_vertices, states);
}
