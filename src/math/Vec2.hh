#pragma once

#include <ostream>

namespace GE::math
{

struct Vec2
{

    float elements[2]{};

    Vec2() noexcept = default;
    Vec2(float _x, float _y) noexcept
    {
        elements[0] = _x;
        elements[1] = _y;
    }

    [[nodiscard]] const float& x() const { return elements[0]; }
    float& x() { return elements[0]; }

    [[nodiscard]] const float& y() const { return elements[1]; }
    float& y() { return elements[1]; }

    inline Vec2& operator+=(const Vec2& v);
    inline Vec2& operator-=(const Vec2& v);
    inline Vec2& operator*=(const Vec2& v);
    inline Vec2& operator/=(const Vec2& v);

    // No need to be friend
    friend std::ostream& operator<<(std::ostream& out, const Vec2& v);
};

Vec2& Vec2::operator+=(const Vec2& v)
{
    this->x() += v.x();
    this->y() += v.y();
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    return *this;
}
Vec2& Vec2::operator*=(const Vec2& v)
{
    this->x() *= v.x();
    this->y() *= v.y();
    return *this;
}
Vec2& Vec2::operator/=(const Vec2& v)
{
    this->x() /= v.x();
    this->y() /= v.y();
    return *this;
}

inline Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2{lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}
inline Vec2 operator-(const Vec2& v)
{
    return Vec2{-v.x(), -v.y()};
}
inline Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
{
    return lhs + (-rhs);
}
inline Vec2 operator*(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2{lhs.x() * rhs.x(), lhs.y() * rhs.y()};
}
inline Vec2 operator/(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2{lhs.x() / rhs.x(), lhs.y() / rhs.y()};
}
inline bool operator==(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}
inline bool operator!=(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
}

inline std::ostream& operator<<(std::ostream& out, const Vec2& v)
{
    out << "Vec2: (" << v.x() << ", " << v.y() << ")\n";
    return out;
}

}
