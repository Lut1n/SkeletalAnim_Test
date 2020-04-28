#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../maths/math_vector.hpp"
#include "Joint.hpp"

#define BONE_COUNT 5
#define BONE_LENGTH 50.f

// --------------------------------------------------------------------------
// Very simple bones animator with constant count and length
class Animator
{
public:
    Animator(int jointCount = BONE_COUNT, float jointLength = BONE_LENGTH);

    // Build a backbone (graph of bones reduced to a simple linked list)
    void buildSkeleton(int count, float length);

    // Update all bone's transforms
    void animate(float elapsed);

    std::vector<Joint*>& joints();

protected:
    std::vector<Joint*> m_joints;
    float m_boneLength;
};

#endif // ANIMATOR_H
