#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../maths/math_vector.hpp"
#include "Join.hpp"

#define BONE_COUNT 5
#define BONE_LENGTH 50.f

struct Animator
{
    Animator(int joinCount = BONE_COUNT, float joinLength = BONE_LENGTH);

    void animate(const Vec2& scene_pos, float ellapsed_ms);

    std::vector<Join*> m_joins;
};

#endif // ANIMATOR_H
