////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  vector2.hpp
//
////////////////////////

#pragma once

#include <sstream>
#include <cmath>

namespace render::math
{
    template<typename T>
    class Vector2
    {
        public:
            Vector2() = default;

            Vector2(T x, T y)
                : x(x),
                  y(y)
            { }

            template<typename U>
            Vector2(const Vector2<U> &other)
                : x(static_cast<T>(other.x)),
                  y(static_cast<T>(other.y))
            { }

            inline T norm()
            {
                return std::sqrt(x * x + y * y);
            }

            inline Vector2<T> unit()
            {
                return *this / norm();
            }

            T x;
            T y;
    };

    template <typename T>
    Vector2<T> operator-(const Vector2<T> &right)
    {
        return Vector2<T>(-right.x, -right.y);
    }

    template <typename T>
    Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right)
    {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    template <typename T>
    Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right)
    {
            left.x -= right.x;
            left.y -= right.y;

            return left;
    }

    template <typename T>
    Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right)
    {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }

    template <typename T>
    Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right)
    {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    template <typename T>
    Vector2<T> operator*(const Vector2<T> &left, T right)
    {
        return Vector2<T>(left.x * right, left.y * right);
    }

    template <typename T>
    Vector2<T> operator*(T left, const Vector2<T> &right)
    {
        return Vector2<T>(right.x * left, right.y * left);
    }

    template <typename T>
    Vector2<T> &operator*=(Vector2<T> &left, T right)
    {
        left.x *= right;
        left.y *= right;

        return left;
    }

    template <typename T>
    Vector2<T> operator/(const Vector2<T> &left, T right)
    {
        return Vector2<T>(left.x / right, left.y / right);
    }

    template <typename T>
    Vector2<T> &operator/=(Vector2<T> &left, T right)
    {
        left.x /= right;
        left.y /= right;

        return left;
    }

    template <typename T>
    bool operator==(const Vector2<T> &left, const Vector2<T> &right)
    {
        return (left.x == right.x) && (left.y == right.y);
    }

    template <typename T>
    bool operator!=(const Vector2<T> &left, const Vector2<T> &right)
    {
        return (left.x != right.x) || (left.y != right.y);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &stream, const Vector2<T> &vec)
    {
        stream << vec.x << " ";
        stream << vec.y;

        return stream;
    }

    template<typename T>
    std::istream &operator>>(std::istream &data, Vector2<T> &vec)
    {
        data >> vec.x;
        data >> vec.y;

        return data;
    }

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
}
