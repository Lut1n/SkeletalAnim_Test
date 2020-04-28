#include "Joint.hpp"

// --------------------------------------------------------------------------
Joint::Joint(sf::Transform initPose)
    : m_initPose(initPose)
    , m_pose(initPose)
{
}

// --------------------------------------------------------------------------
Joint::~Joint()
{
}

// --------------------------------------------------------------------------
void Joint::computeInitTransform()
{
    sf::Transform initialTransform = sf::Transform::Identity;

    Joint* curr = this;
    while(curr)
    {
        initialTransform = curr->m_initPose * initialTransform;
        curr = static_cast<Joint*>(curr->m_parent);
    }

    m_initTransform = initialTransform;
    m_inverseInitTransform = initialTransform.getInverse();
}

// --------------------------------------------------------------------------
void Joint::setPose(const Vec2& polar)
{
    m_pose = sf::Transform::Identity;
    m_pose.rotate(polar.y).translate(0,-polar.x);
}
// --------------------------------------------------------------------------
void Joint::updateTransform()
{
    m_transform = sf::Transform::Identity;
    
    Joint* curr = this;
    while(curr)
    {
        m_transform = curr->m_pose * m_transform;
        curr = dynamic_cast<Joint*>(curr->m_parent);
    }
}

// --------------------------------------------------------------------------
Vec2 Joint::getPoseVec()
{
     return m_pose * Vec2(0,0);
}

// --------------------------------------------------------------------------
Vec2 Joint::tail()
{
    Vec2 pt;
    if(m_parent) pt = static_cast<Joint*>(m_parent)->head();
    return pt;
}

// --------------------------------------------------------------------------
Vec2 Joint::head()
{
    Vec2 pt = m_initTransform * Vec2(0.0,0.0);
    return pt;
}

// --------------------------------------------------------------------------
float Joint::distanceFrom(const Vec2& pt)
{
    Vec2 p1 = tail();
    Vec2 p2 = head();

    float d1 = distance(pt,p1);
    float d2 = distance(pt,p2);

    Vec2 p12 = p2-p1;
    Vec2 p1pt = pt-p1;
    Vec2 t = normalize(p12);
    Vec2 n = getNormal(t);

    float p = dot(t,p1pt);
    float d3 = dot(n,p1pt);
    float l = len(p12);

    float res = std::min(d1,d2);
    if(p > 0.0 && p < l)
    {
        res = std::min(d3,res);
    }

    return res;
}

// --------------------------------------------------------------------------
Vec2 Joint::closestPoint(const Vec2& pt)
{
    Vec2 p1 = tail();
    Vec2 p2 = head();

    float d1 = distance(pt,p1);
    float d2 = distance(pt,p2);
    Vec2 t = normalize(p2-p1);
    float p = dot(t,pt-p1);

    float d = distanceFrom(pt);

    if(d == d1) return p1;
    if(d == d2) return p2;
    else return p1 + t*p;
}

// --------------------------------------------------------------------------
sf::Transform Joint::root2Joint()
{
    return m_transform;
}

// --------------------------------------------------------------------------
sf::Transform Joint::animTransform()
{
    return m_transform * m_inverseInitTransform;
}

// --------------------------------------------------------------------------
Joint* Joint::parentJoint() const
{
    return static_cast<Joint*>(m_parent);
}

// --------------------------------------------------------------------------
std::map<float,int> Joint::findClosest(Vec2 vertex, const std::vector<Joint*>& joints)
{
    std::map<float,int> ordered;
    for(int i=0;i<(int)joints.size();++i)
    {
        float l = joints[i]->distanceFrom(vertex);
        ordered[l] = i;
    }

    return ordered;
}
