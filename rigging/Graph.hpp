#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <algorithm>

struct GraphNode
{
    GraphNode* m_parent;
    std::vector<GraphNode*> m_children;
    
    GraphNode();
    virtual ~GraphNode();

    void addChild(GraphNode* child);
    void removeChild(GraphNode* child);
    
private:
    
    void attachChild(GraphNode* child);
    void detachChild(GraphNode* child);
};

#endif // GRAPH_HPP
