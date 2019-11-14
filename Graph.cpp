#include "Graph.hpp"
#include <algorithm>

GraphNode::GraphNode() : m_parent(nullptr) {}
GraphNode::~GraphNode() {}

void GraphNode::addChild(GraphNode* child)
{
    if(child->m_parent != nullptr)
        child->m_parent->detachChild(child);
        
    attachChild(child);
    child->m_parent = this;
}

void GraphNode::removeChild(GraphNode* child)
{
    detachChild(child);
    child->m_parent = nullptr;
}

void GraphNode::attachChild(GraphNode* child)
{
    auto found = std::find(m_children.begin(),m_children.end(),child);
    if(found == m_children.end()) m_children.push_back(child);
}

void GraphNode::detachChild(GraphNode* child)
{
    auto found = std::find(m_children.begin(),m_children.end(),child);
    if(found != m_children.end()) m_children.erase(found);
}
