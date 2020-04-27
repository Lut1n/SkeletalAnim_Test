#ifndef MATH_VECTOR_INCLUDED
#define MATH_VECTOR_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

// --------------------------------------------------------------------------
// helpers for angle conversion
#define Pi 3.1415927410125732421875
#define Deg2Rad Pi/180
#define Rad2Deg 180/Pi

// --------------------------------------------------------------------------
// Alias for sfml vector
using Vec2 = sf::Vector2f;
template<typename T>
using Arr = std::vector<T>;


// --------------------------------------------------------------------------
// dot product
float dot( const Vec2& v1, const Vec2& v2 );

// --------------------------------------------------------------------------
// square length of a vector
float len2( const Vec2& v );

// --------------------------------------------------------------------------
// length of a vector
float len( const Vec2& v );

// --------------------------------------------------------------------------
// distance between two points
float distance( const Vec2& p1, const Vec2& p2 );

// --------------------------------------------------------------------------
// normalize vector2f
Vec2 normalize( const Vec2& v );

// --------------------------------------------------------------------------
// compute normal of a direction ( as a vector at +90° from dir )
Vec2 getNormal(const Vec2& dir);

// --------------------------------------------------------------------------
// compute normal of a segment ab ( as a vector at +90° from (b-a) )
Vec2 getNormal(const Vec2& a, const Vec2& b);

// --------------------------------------------------------------------------
// test if vector v is on the positive side of a segment ab (using normal)
bool above(Vec2 v, Vec2 a, Vec2 b);

// --------------------------------------------------------------------------
// compute z component of a cross product
float crossZ(const Vec2& v1, const Vec2& v2);

// --------------------------------------------------------------------------
// sign of a float
float sign(float f);

// --------------------------------------------------------------------------
// vec2 linear interpolation
Vec2 mix(Vec2& v1, Vec2& v2, float t = 0.5f);


#endif // MATH_VECTOR_INCLUDED
