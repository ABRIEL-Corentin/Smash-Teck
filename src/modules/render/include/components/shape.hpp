////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  shape.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"
#include "math/vector2.hpp"
#include "math/rect.hpp"
#include "math/color.hpp"
#include <iostream>

namespace render
{
    using Shape = struct Shape
    {
        std::size_t id;
        std::size_t texture_id;

        /// @brief Update texture from label
        /// @param texture_label texture label to apply
        void setTexture(const std::string &texture_label);

        /// @brief Update texture from id
        /// @param texture_id texture id to apply
        void setTexture(std::size_t texture_id);

        /// @brief Get the current color of the shape
        /// @return the current color
        math::Color getColor() const;

        /// @brief Set the new color
        /// @param color the new color
        void setColor(const math::Color &color);

        /// @brief Get the current size
        /// @return the current size
        math::Vector2f getSize() const;

        /// @brief Define the size of this shape
        /// @param size new size
        void setSize(const math::Vector2f &size);

        /// @brief Define the size of this shape
        /// @param width new horizontal size
        /// @param height new vertical size
        void setSize(float width, float height);

        /// @brief Get the current scale
        /// @return the current scale
        math::Vector2f getScale() const;

        /// @brief Define the scale of this shape
        /// @param size new scale
        void setScale(const math::Vector2f &scale);

        /// @brief Define the scale of this shape
        /// @param width new horizontal scale
        /// @param height new vertical scale
        void setScale(float width, float height);

        /// @brief Get the current position
        /// @return the current position
        math::Vector2f getPosition() const;

        /// @brief Update position
        /// @param position new position
        void setPosition(const math::Vector2f &position);

        /// @brief Update position
        /// @param x new horizontal position
        /// @param y new vertical position
        void setPosition(float x, float y);

        /// @brief Move the shape
        /// @param offset offset to move
        void move(const math::Vector2f &offset);

        /// @brief Move the shape
        /// @param x horizontal offset to move
        /// @param y vertical offset to move
        void move(float x, float y);

        /// @brief Get rect of shape
        /// @return current rect
        math::Rectf getRect() const;

        /// @brief Update rect of shape
        /// @param rect new rect (position and size)
        void setRect(const math::Rectf &rect);

        /// @brief Get the current rotation
        /// @return the current rotation
        float getRotation() const;

        /// @brief Update the rotation
        /// @param angle the new rotation
        void setRotation(float angle);

        /// @brief Rotate the shape
        /// @param angle angle to rotate
        void rotate(float angle);

        /// @brief Container for manipulate and display 2D shape
        /// @param texture_label texture to apply on this shape
        /// @param position position (center) of this shape
        /// @param size size of this shape
        /// @param rotation rotation of this shape
        Shape(const engine::ecs::Entity &entity, std::istream &data);

        /// @brief Destroy graphical shape data
        void onDestroy();
    };
}
