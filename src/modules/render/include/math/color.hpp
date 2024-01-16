////////////////////////
//
//  Created on Sat Sep 30 2023
//
//  color.hpp
//
////////////////////////

#pragma once

#include <sstream>

namespace render::math
{
    class Color
    {
        public:
            Color();
            Color(float r, float g, float b, float a = 255);

            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color Yellow;
            static const Color Magenta;
            static const Color Cyan;
            static const Color Transparent;

            bool operator==(const Color &other);
            bool operator!=(const Color &other);
            Color operator+(const Color &other);
            Color operator-(const Color &other);
            Color &operator+=(const Color &other);
            Color &operator-=(const Color &other);
            Color operator*(const float &value);
            Color operator/(const float &value);
            Color &operator*=(const float &value);
            Color &operator/=(const float &value);

            float r;
            float g;
            float b;
            float a;
    };

    std::ostream &operator<<(std::ostream &stream, const Color &color);
    Color &operator>>(std::istream &stream, Color &color);
}
