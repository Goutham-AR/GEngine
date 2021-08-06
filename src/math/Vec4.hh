#pragma once

#include <ostream>

#include "Vec2.hh"
#include "Vec3.hh"

namespace GE::math
{

struct Vec4
{
    float elements[4]{};

    Vec4() noexcept = default;
    inline Vec4(float _x, float _y, float _z, float _w) noexcept
    {
        elements[0] = _x;
        elements[1] = _y;
        elements[2] = _z;
        elements[3] = _w;
    }
    inline Vec4(const Vec2& v, float _z, float _w)
    {
        elements[0] = v.x();
        elements[1] = v.y();
        elements[2] = _z;
        elements[3] = _w;
    }
    inline Vec4(const Vec2& v, const Vec2& u)
    {
        elements[0] = v.x();
        elements[1] = v.y();
        elements[2] = u.x();
        elements[3] = u.y();
    }
    inline Vec4(const Vec3& v, float _w)
    {
        elements[0] = v.x();
        elements[1] = v.y();
        elements[2] = v.z();
        elements[3] = _w;
    }

    [[nodiscard]] const float& x() const { return elements[0]; }
    float& x() { return elements[0]; }

    [[nodiscard]] const float& y() const { return elements[1]; }
    float& y() { return elements[1]; }

    [[nodiscard]] const float& z() const { return elements[2]; }
    float& z() { return elements[2]; }

    [[nodiscard]] const float& w() const { return elements[3]; }
    float& w() { return elements[3]; }

    inline Vec4& operator+=(const Vec4& v);
    inline Vec4& operator-=(const Vec4& v);
    inline Vec4& operator*=(const Vec4& v);
    inline Vec4& operator/=(const Vec4& v);

    // No need to be friend
    friend std::ostream& operator<<(std::ostream& out, const Vec4& v);
};

Vec4& Vec4::operator+=(const Vec4& v)
{
    this->x() += v.x();
    this->y() += v.y();
    this->z() += v.z();
    this->w() += v.w();
    return *this;
}
Vec4& Vec4::operator-=(const Vec4& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    this->z() -= v.z();
    this->w() -= v.w();
    return *this;
}
Vec4& Vec4::operator*=(const Vec4& v)
{
    this->x() *= v.x();
    this->y() *= v.y();
    this->z() *= v.z();
    this->w() *= v.w();
    return *this;
}
Vec4& Vec4::operator/=(const Vec4& v)
{
    this->x() /= v.x();
    this->y() /= v.y();
    this->z() /= v.z();
    this->w() /= v.w();
    return *this;
}

inline Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4{lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w()};
}
inline Vec4 operator-(const Vec4& v)
{
    return Vec4{-v.x(), -v.y(), -v.z(), -v.w()};
}
inline Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
{
    return lhs + (-rhs);
}
inline Vec4 operator*(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4{lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z(), lhs.w() * rhs.w()};
}
inline Vec4 operator/(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4{lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z(), lhs.w() / rhs.w()};
}
inline bool operator==(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() && lhs.w() == lhs.w());
}
inline bool operator!=(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z() || lhs.w() != lhs.w());
}

inline std::ostream& operator<<(std::ostream& out, const Vec4& v)
{
    out << "Vec4: ("
        << v.x() << ", "
        << v.y() << ", "
        << v.z() << ", "
        << v.w() << ")\n";
    return out;
}

}
