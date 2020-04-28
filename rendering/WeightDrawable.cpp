#include "WeightDrawable.hpp"
#include "vertex_shader.hpp"
#include <cmath>
#include <iostream>

#define VERTEX_COUNT 10
#define SKIN_LEN 300

// --------------------------------------------------------------------------
sf::Shader WeightDrawable::s_shader;
sf::Shader WeightDrawable::s_shaderWeight;
bool WeightDrawable::s_assetsLoaded = false;

// --------------------------------------------------------------------------
WeightDrawable::WeightDrawable()
{
    if(s_assetsLoaded == false)
    {
        s_shader.loadFromMemory(s_riggingVertCode_skin, sf::Shader::Vertex);
        s_shaderWeight.loadFromMemory(s_riggingVert_weights, sf::Shader::Vertex);
        s_assetsLoaded = true;
    }

}

// --------------------------------------------------------------------------
void WeightDrawable::setup(const sf::VertexArray& vertices, const std::vector<Joint*>& joints)
{
    m_joints = joints;
    m_matrices.resize(m_joints.size(), sf::Transform::Identity);


    int edgeCount = 4 * vertices.getVertexCount() - 6;
    int edgeIndex = 0;
    m_edgeShape = sf::VertexArray(sf::Lines, edgeCount);
    for(std::uint32_t i=2; i<vertices.getVertexCount(); i+=2)
    {
        m_edgeShape[edgeIndex].position = vertices[i-2].position;
        m_edgeShape[edgeIndex+1].position = vertices[i-1].position;
        m_edgeShape[edgeIndex].color = vertices[i-2].color;
        m_edgeShape[edgeIndex+1].color = vertices[i-1].color;
        edgeIndex+=2;

        m_edgeShape[edgeIndex].position = vertices[i-1].position;
        m_edgeShape[edgeIndex+1].position = vertices[i+1].position;
        m_edgeShape[edgeIndex].color = vertices[i-1].color;
        m_edgeShape[edgeIndex+1].color = vertices[i+1].color;
        edgeIndex+=2;

        m_edgeShape[edgeIndex].position = vertices[i-2].position;
        m_edgeShape[edgeIndex+1].position = vertices[i].position;
        m_edgeShape[edgeIndex].color = vertices[i-2].color;
        m_edgeShape[edgeIndex+1].color = vertices[i].color;
        edgeIndex+=2;

        m_edgeShape[edgeIndex].position = vertices[i-1].position;
        m_edgeShape[edgeIndex+1].position = vertices[i].position;
        m_edgeShape[edgeIndex].color = vertices[i-1].color;
        m_edgeShape[edgeIndex+1].color = vertices[i].color;
        edgeIndex+=2;
    }

    // two lasts
    int i = vertices.getVertexCount();
    m_edgeShape[edgeIndex].position = vertices[i-2].position;
    m_edgeShape[edgeIndex+1].position = vertices[i-1].position;
    m_edgeShape[edgeIndex].color = vertices[i-2].color;
    m_edgeShape[edgeIndex+1].color = vertices[i-1].color;

    int weightCount = 4 * vertices.getVertexCount();
    int weightIndex = 0;
    m_weightLineShape = sf::VertexArray(sf::Lines, weightCount);

    for(std::uint32_t i=0;i<vertices.getVertexCount();++i)
    {
        std::map<float,int> cj = Joint::findClosest(vertices[i].position, m_joints);
        int closest = cj.begin()->second;

        m_weightLineShape[weightIndex].position = vertices[i].position;
        m_weightLineShape[weightIndex+1].position = (m_joints[closest]->head() + m_joints[closest]->tail())*0.5f;
        m_weightLineShape[weightIndex].color = vertices[i].color;
        m_weightLineShape[weightIndex+1].color = vertices[i].color;
        weightIndex+=2;
    }
}

// --------------------------------------------------------------------------
void WeightDrawable::setShaderParameters()
{
    int boneCount = m_joints.size();

    for(int i=0;i<boneCount;++i) m_matrices[i] = m_joints[i]->animTransform();
    s_shader.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shader.setUniform("u_jointCount",float(boneCount));

    s_shaderWeight.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shaderWeight.setUniform("u_jointCount",float(boneCount));
}

// --------------------------------------------------------------------------
void WeightDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();

    states.shader = &s_shader;
    target.draw(m_edgeShape, states);

    states.shader = &s_shaderWeight;
    target.draw(m_weightLineShape, states);
}
