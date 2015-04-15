//
//  Vec2.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_Vec2_h
#define BenchingBall_Vec2_h

#include <cmath>

namespace BenchingBall {

struct Vec2
{
    Vec2 operator+(const Vec2 &aRhs) const
    {
        return {x+aRhs.x, y+aRhs.y};
    }

    Vec2 operator-(const Vec2 &aRhs) const
    {
        return *this + (aRhs * -1);
    }

    Vec2 &operator-()
    {
        x = -x;
        y = -y;
        return *this;
    }

    Vec2 & operator+=(const Vec2 &aRhs)
    {
        x += aRhs.x;
        y += aRhs.y;
        return *this;
    }

    Vec2 & operator-=(const Vec2 &aRhs)
    {
        x -= aRhs.x;
        y -= aRhs.y;
        return *this;
    }

    Vec2 operator*(double k) const
    {
        return {x*k, y*k};
    }

    double dot(const Vec2 &aRhs) const
    {
        return x*aRhs.x + y*aRhs.y;
    }

    Vec2 &normalize()
    {
        double len = length();
        x /= len;
        y /= len;
        return *this;
    }

    double length() const
    {
        return std::sqrt(x*x + y*y);
    }

    double x;
    double y;
};

inline double distance(const Vec2 &aLhs, const Vec2 &aRhs)
{
    return (aLhs-aRhs).length();
}


} // namespace BenchingBall

#endif
