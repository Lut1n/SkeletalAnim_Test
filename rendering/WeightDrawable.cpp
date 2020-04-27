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
        s_shader.loadFromMemory(vertCode, sf::Shader::Vertex);
        s_shaderWeight.loadFromMemory(vertCode_weights, sf::Shader::Vertex);
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

    int weightCount = 4 * vertices.getVertexCount();
    int weightIndex = 0;
    m_lineShape = sf::VertexArray(sf::Lines, weightCount);

    for(std::uint32_t i=0;i<vertices.getVertexCount();++i)
    {
        std::map<float,int> cj = Joint::findClosest(vertices[i].position, m_joints);
        int closest = cj.begin()->second;

        m_lineShape[weightIndex].position = vertices[i].position;
        m_lineShape[weightIndex+1].position = (m_joints[closest]->head() + m_joints[closest]->tail())*0.5f;
        m_lineShape[weightIndex].color = vertices[i].color;
        m_lineShape[weightIndex+1].color = vertices[i].color;
        weightIndex+=2;
    }
}

// --------------------------------------------------------------------------
void WeightDrawable::setShaderParameters()
{
    int boneCount = m_joints.size();

    for(int i=0;i<boneCount;++i) {
        m_matrices[i] = m_joints[i]->m_transform * m_joints[i]->m_inverseInitTransform;
    }
    s_shader.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shader.setUniform("u_jointCount",float(boneCount));

    s_shaderWeight.setUniformArray("u_jointTransforms", m_matrices.data(), m_matrices.size());
    s_shaderWeight.setUniform("u_jointCount",float(boneCount));
}

// --------------------------------------------------------------------------
void WeightDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();

    if(displayGrid)
    {
        states.shader = &s_shader;
        target.draw(m_edgeShape, states);
    }

    if(displayWeight)
    {
        states.shader = &s_shaderWeight;
        target.draw(m_lineShape, states);
    }
}
