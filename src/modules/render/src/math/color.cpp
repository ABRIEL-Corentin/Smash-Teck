////////////////////////
//
//  Created on Sat Sep 30 2023
//
//  color.cpp
//
////////////////////////

#include "math/color.hpp"

namespace render::math
{
    const Color Color::Black = Color(0, 0, 0);
    const Color Color::White = Color(255, 255, 255);
    const Color Color::Red = Color(255, 0, 0);
    const Color Color::Green = Color(0, 255, 0);
    const Color Color::Blue = Color(0, 0, 255);
    const Color Color::Yellow = Color(255, 255, 0);
    const Color Color::Magenta = Color(255, 0, 255);
    const Color Color::Cyan = Color(0, 255, 255);
    const Color Color::Transparent = Color(0, 0, 0, 0);

    Color::Color()
        : r(255),
          g(255),
          b(255),
          a(255)
    { }

    Color::Color(float r, float g, float b, float a)
        : r(r),
          g(g),
          b(b),
          a(a)
    { }

    bool Color::operator==(const Color &other)
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool Color::operator!=(const Color &other)
    {
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }

    Color Color::operator+(const Color &other)
    {
        return Color(
            r + other.r,
            g + other.g,
            b + other.b,
            a + other.a
        );
    }

    Color Color::operator-(const Color &other)
    {
        return Color(
            r - other.r,
            g - other.g,
            b - other.b,
            a - other.a
        );
    }

    Color &Color::operator+=(const Color &other)
    {
        r += other.r;
        g += other.g;
        b += other.b;
        a += other.a;

        return *this;
    }

    Color &Color::operator-=(const Color &other)
    {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        a -= other.a;

        return *this;
    }

    Color Color::operator*(const float &value)
    {
        return Color(
            r * value,
            g * value,
            b * value,
            a * value
        );
    }

    Color Color::operator/(const float &value)
    {
        return Color(
            r / value,
            g / value,
            b / value,
            a / value
        );
    }

    Color &Color::operator*=(const float &value)
    {
        r *= value;
        g *= value;
        b *= value;
        a *= value;

        return *this;
    }

    Color &Color::operator/=(const float &value)
    {
        r /= value;
        g /= value;
        b /= value;
        a /= value;

        return *this;
    }

    std::ostream &operator<<(std::ostream &stream, const Color &color)
    {
        stream << color.r << " ";
        stream << color.g << " ";
        stream << color.b << " ";
        stream << color.a;

        return stream;
    }

    Color &operator>>(std::istream &stream, Color &color)
    {
        stream >> color.r;
        stream >> color.g;
        stream >> color.b;
        stream >> color.a;

        return color;
    }
}
