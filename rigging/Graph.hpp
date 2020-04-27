#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <algorithm>

// --------------------------------------------------------------------------
// Define a basic doubly linked graph node structure
class GraphNode
{
public:
    GraphNode();
    virtual ~GraphNode();

    // set a node as child and make this one parent of it
    void addChild(GraphNode* child);

    // break parent/child links
    void removeChild(GraphNode* child);

    // get parent
    GraphNode* parent();

    // get children
    std::vector<GraphNode*>& children();
    
protected:
    void attachChild(GraphNode* child);
    void detachChild(GraphNode* child);

    GraphNode* m_parent;
    std::vector<GraphNode*> m_children;
};

#endif // GRAPH_HPP
