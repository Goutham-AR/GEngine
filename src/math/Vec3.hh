#pragma once

#include <ostream>

#include "Vec2.hh"

namespace GE::math
{

struct Vec3
{
    float elements[3]{};

    Vec3() noexcept = default;
    Vec3(float _x, float _y, float _z) noexcept
    {
        elements[0] = _x;
        elements[1] = _y;
        elements[2] = _z;
    }

    Vec3(const Vec2& v, float _z)
    {
        elements[0] = v.x();
        elements[1] = v.y();
        elements[2] = _z;
    }

    [[nodiscard]] const float& x() const { return elements[0]; }
    float& x() { return elements[0]; }

    [[nodiscard]] const float& y() const { return elements[1]; }
    float& y() { return elements[1]; }

    [[nodiscard]] const float& z() const { return elements[2]; }
    float& z() { return elements[2]; }

    inline Vec3& operator+=(const Vec3& v);
    inline Vec3& operator-=(const Vec3& v);
    inline Vec3& operator*=(const Vec3& v);
    inline Vec3& operator/=(const Vec3& v);

    // No need to be friend
    friend std::ostream& operator<<(std::ostream& out, const Vec3& v);
};

Vec3& Vec3::operator+=(const Vec3& v)
{
    this->x() += v.x();
    this->y() += v.y();
    this->z() += v.z();
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    this->z() -= v.z();
    return *this;
}
Vec3& Vec3::operator*=(const Vec3& v)
{
    this->x() *= v.x();
    this->y() *= v.y();
    this->z() *= v.z();
    return *this;
}
Vec3& Vec3::operator/=(const Vec3& v)
{
    this->x() /= v.x();
    this->y() /= v.y();
    this->z() /= v.z();
    return *this;
}

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3{lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z()};
}
inline Vec3 operator-(const Vec3& v)
{
    return Vec3{-v.x(), -v.y(), -v.z()};
}
inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return lhs + (-rhs);
}
inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3{lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z()};
}
inline Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3{lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z()};
}
inline bool operator==(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}
inline bool operator!=(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.z() != rhs.z());
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    out << "Vec3: (" << v.x() << ", " << v.y() << ", " << v.z() << ")\n";
    return out;
}

}
