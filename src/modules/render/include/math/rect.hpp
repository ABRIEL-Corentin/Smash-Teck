////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  rect.hpp
//
////////////////////////

#pragma once

#include "vector2.hpp"
#include <algorithm>

namespace render::math
{
    template<typename T>
    class Rect
    {
        public:
            Rect() = default;

            Rect(T left, T top, T width, T height)
                : left(left),
                  top(top),
                  width(width),
                  height(height)
            { }

            Rect(const Vector2<T> &position, const Vector2<T> &size)
                : left(position.x),
                  top(position.y),
                  width(size.x),
                  height(size.y)
            { }

            template<typename U>
            Rect(const Rect<U> &other)
                : left(static_cast<T>(other.left)),
                  top(static_cast<T>(other.top)),
                  width(static_cast<T>(other.width)),
                  height(static_cast<T>(other.height))
            { }

            bool contains(T x, T y) const
            {
                T minX = std::min(left, static_cast<T>(left + width));
                T maxX = std::max(left, static_cast<T>(left + width));
                T minY = std::min(top, static_cast<T>(top + height));
                T maxY = std::max(top, static_cast<T>(top + height));

                return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
            }

            inline bool contains(const Vector2<T> &point) const
            {
                return contains(point.x, point.y);
            }

            bool intersects(const Rect<T> &rect) const
            {
                float leftA = left - width * 0.5f;
                float leftB = rect.left - rect.width * 0.5f;
                float rightA = left + width * 0.5f;
                float rightB = rect.left + rect.width * 0.5f;
                float topA = top - height * 0.5f;
                float topB = rect.top - rect.height * 0.5f;
                float bottomA = top + height * 0.5f;
                float bottomB = rect.top + rect.height * 0.5f;

                return bottomA >= topB && topA <= bottomB && rightA >= leftB && leftA <= rightB;
            }

            inline Vector2<T> getPosition() const
            {
                return Vector2<T>(left, top);
            }

            inline Vector2<T> getSize() const
            {
                return Vector2<T>(width, height);
            }

            T left;
            T top;
            T width;
            T height;
    };

    using Rectf = Rect<float>;

    template <typename T>
    bool operator==(const Rect<T>& left, const Rect<T>& right)
    {
        return (left.left == right.left) && (left.width == right.width) &&
            (left.top == right.top) && (left.height == right.height);
    }

    template <typename T>
    bool operator!=(const Rect<T>& left, const Rect<T>& right)
    {
        return !(left == right);
    }
}
