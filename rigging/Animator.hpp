#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../maths/math_vector.hpp"
#include "Joint.hpp"

#define BONE_COUNT 5
#define BONE_LENGTH 50.f

struct Animator
{
    Animator(int jointCount = BONE_COUNT, float jointLength = BONE_LENGTH);

    void animate(const Vec2& scene_pos, float ellapsed_ms);

    std::vector<Joint*> m_joints;
};

#endif // ANIMATOR_H
