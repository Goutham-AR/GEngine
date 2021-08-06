#pragma once

#include <ostream>
#include <cmath>

#include "Vec3.hh"
#include "Vec4.hh"

namespace GE::math
{

constexpr float PI = 3.14159265f;

inline float toRadians(float degrees)
{
    return (PI / 180.0f) * degrees;
}

struct Mat4
{

private:
    float elements[4 * 4]{};

    float& operator[](size_t i) { return elements[i]; }
    const float& operator[](size_t i) const { return elements[i]; }

public:
    Mat4() = default;
    explicit Mat4(float diagonalVal)
    {
        this->at(0, 0) = diagonalVal;
        this->at(1, 1) = diagonalVal;
        this->at(2, 2) = diagonalVal;
        this->at(3, 3) = diagonalVal;
    }

    float& at(size_t row, size_t col)
    {
        return elements[row + col * 4];
    }

    [[nodiscard]] const float& at(size_t row, size_t col) const
    {
        return elements[row + col * 4];
    }

    Mat4& operator*=(const Mat4& lhs);

    static Mat4 id();
    static Mat4 trans(const Vec3& position);
    static Mat4 rot(float angle, const Vec3& axis);
    static Mat4 scale(const Vec3& scale);
    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);
    static Mat4 perspective(float fov, float aspectRatio, float near, float far);

    friend Mat4 operator+(const Mat4& lhs, const Mat4& rhs);
    friend Mat4 operator-(const Mat4& mat);
};

inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
    Mat4 product{};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            float sum = 0.0f;
            for (int e = 0; e < 4; ++e)
            {
                sum += lhs.at(i, e) * rhs.at(e, j);
            }
            product.at(i, j) = sum;
        }
    }
    return product;
}

inline Mat4 operator+(const Mat4& lhs, const Mat4& rhs)
{
    Mat4 sumMat{};
    for (int i = 0; i < 4 * 4; ++i)
    {
        sumMat[i] = lhs[i] + rhs[i];
    }
    return sumMat;
}

inline Mat4 operator-(const Mat4& mat)
{
    Mat4 negativeMat{};
    for (int i = 0; i < 4 * 4; ++i)
    {
        negativeMat[i] = -mat[i];
    }
    return negativeMat;
}

inline Mat4 operator-(const Mat4& lhs, const Mat4& rhs)
{
    return lhs + (-rhs);
}

inline Mat4& Mat4::operator*=(const Mat4& lhs)
{
    *this = (*this) * lhs;
    return *this;
}

inline Mat4 Mat4::id()
{
    return Mat4{1.0f};
}

inline Mat4 Mat4::trans(const Vec3& position)
{
    Mat4 result{1.0f};

    result.at(0, 3) = position.x();
    result.at(1, 3) = position.y();
    result.at(2, 3) = position.z();

    return result;
}
inline Mat4 Mat4::rot(float angleInDegrees, const Vec3& axis)
{
    Mat4 result{1.0f};

    auto angleInRadian = toRadians(angleInDegrees);
    auto cosine = std::cos(angleInRadian);
    auto sine = std::sin(angleInRadian);

    auto x = axis.x();
    auto y = axis.y();
    auto z = axis.z();

    result.at(0, 0) = x * x * (1.0f - cosine) + cosine;
    result.at(1, 0) = y * x * (1.0f - cosine) + z * sine;
    result.at(2, 0) = x * z * (1.0f - cosine) - y * sine;

    result.at(0, 1) = x * y * (1.0f - cosine) - z * sine;
    result.at(1, 1) = y * y * (1.0f - cosine) + cosine;
    result.at(2, 1) = y * z * (1.0f - cosine) + x * sine;

    result.at(0, 2) = x * z * (1.0f - cosine) + y * sine;
    result.at(1, 2) = y * z * (1.0f - cosine) - x * sine;
    result.at(2, 2) = z * z * (1.0f - cosine) + cosine;

    return result;
}
inline Mat4 Mat4::scale(const Vec3& scale)
{
    Mat4 result{1.0f};

    result.at(0, 0) = scale.x();
    result.at(1, 1) = scale.y();
    result.at(2, 2) = scale.z();

    return result;
}
inline Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 result{1.0f};
    result.at(0, 0) = 2.0f / (right - left);
    result.at(1, 1) = 2.0f / (top - bottom);
    result.at(2, 2) = 2.0f / (near - far);

    result.at(0, 3) = (left + right) / (left - right);
    result.at(1, 3) = (bottom + top) / (bottom - top);
    result.at(2, 3) = (far + near) / (far - near);

    return result;
}

inline Mat4 Mat4::perspective(float fovInDegrees, float aspectRatio, float near, float far)
{
    Mat4 result{};

    auto q = 1.0f / std::tan(toRadians(0.5f * fovInDegrees));
    auto a = q / aspectRatio;

    result.at(0, 0) = a;
    result.at(1, 1) = q;
    result.at(2, 2) = (near + far) / (near - far);
    result.at(3, 2) = -1.0f;
    result.at(2, 3) = (2.0f * far * near) / (near - far);

    return result;
}

inline std::ostream& operator<<(std::ostream& out, const Mat4& mat)
{
    out << "Mat4:\n";
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            out << mat.at(row, col) << "\t";
        }
        out << "\n";
    }

    return out;
}

}