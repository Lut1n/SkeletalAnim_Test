#include "math_vector.hpp"
#include <cmath>

// --------------------------------------------------------------------------
float dot( const Vec2& v1, const Vec2& v2 )
{
    return v1.x*v2.x + v1.y*v2.y;
}

// --------------------------------------------------------------------------
float len2( const Vec2& v )
{
    return dot(v,v);
};

// --------------------------------------------------------------------------
float len( const Vec2& v )
{
    return std::sqrt( dot(v,v) );
};

// --------------------------------------------------------------------------
float distance( const Vec2& p1, const Vec2& p2 )
{
    return len(p2-p1);
}

// --------------------------------------------------------------------------
Vec2 normalize( const Vec2& v )
{
    return v / len(v);
}

// --------------------------------------------------------------------------
float crossZ(const Vec2& v1, const Vec2& v2)
{
    return v1.x*v2.y - v2.x*v1.y;
}

// --------------------------------------------------------------------------
Vec2 cart2polar(const Vec2& cart)
{
    float m = len(cart);
    float a;

    if(cart.x == 0.0) a = sign(cart.y) * Pi/2;
    else a = atan2f(cart.y, cart.x);

    return Vec2(m,a);
}

// --------------------------------------------------------------------------
Vec2 polar2cart(const Vec2& polar)
{
    float x = std::cos(polar.y) * polar.x;
    float y = std::sin(polar.y) * polar.x;
    return Vec2(x,y);
}

// --------------------------------------------------------------------------
float sign(float f)
{
    return f>0.0?1.0:(f<0.0?-1.0:0.0);
}

// --------------------------------------------------------------------------
Vec2 mix(Vec2& v1, Vec2& v2, float t)
{
    return (v2-v1) * t + v1;
}

// --------------------------------------------------------------------------
Vec2 getNormal(const Vec2& dir)
{
    Vec2 t = normalize( dir );
    return Vec2(-t.y, t.x);
}

// --------------------------------------------------------------------------
Vec2 getNormal(const Vec2& a, const Vec2& b)
{
    return getNormal(b-a);
}

// --------------------------------------------------------------------------
bool above(Vec2 v, Vec2 a, Vec2 b)
{
    float cz = crossZ( v-a, b-a );
    return cz > 0.0;
}
