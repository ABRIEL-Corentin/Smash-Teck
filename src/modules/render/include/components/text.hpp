////////////////////////
//
//  Created on Wed Sep 27 2023
//
//  text.hpp
//
////////////////////////

#pragma once

#include "math/vector2.hpp"
#include "math/color.hpp"
#include "ecs/world.hpp"
#include "utils.hpp"

namespace render
{
    using Text = struct Text
    {
        std::size_t id;
        std::size_t font_id;

        /// @brief Set font of text with label
        /// @param font_label label of font
        void setFont(const std::string &font_label);

        /// @brief Set font of text with id
        /// @param font_id id of font
        void setFont(std::size_t font_id);

        /// @brief Get the current color of the text
        /// @return the current color
        math::Color getColor() const;

        /// @brief Set a new color for a text
        /// @param color a new color
        void setColor(const math::Color &color);

        /// @brief Get Size of text
        /// @return size of text
        math::Vector2f getSize() const;

        /// @brief Get character size of text
        /// @return character size
        std::size_t getCharacterSize() const;

        /// @brief Set character size of text
        /// @param size new character size
        void setCharacterSize(std::size_t size);

        /// @brief Get the position of text
        /// @return the current position
        math::Vector2f getPosition() const;

        /// @brief Set the new position of text
        /// @param position new position
        void setPosition(const math::Vector2f &position);

        /// @brief Get the origin of text
        /// @return the current origin of the text
        math::Vector2f getOrigin() const;

        /// @brief Set the origin of the text
        ///         0   -> left or top
        ///         0.5 -> center
        ///         1   -> right or down
        /// @param origin
        void setOrigin(const math::Vector2f &origin);

        /// @brief Move text
        /// @param offset offset to move
        void move(const math::Vector2f &offset);

        /// @brief Get the current totation of text
        /// @return the current rotation
        float getRotation() const;

        /// @brief Set the new rotation of text
        /// @param angle the new rotation
        void setRotation(float angle);

        /// @brief Rotate text
        /// @param angle angle to rotate
        void rotate(float angle);

        /// @brief Get the current str content
        /// @return the current str content
        std::string getStr() const;

        /// @brief Set the new str content
        /// @param str new str content
        void setStr(const std::string &str);

        /// @brief Set the new content with some values
        /// @param args all values to display on text
        template<typename ... ARGS>
        inline void setStr(const ARGS &... args)
        {
            setStr(engine::concat(args...));
        }

        /// @brief Container for display and manage a text
        /// @param font_label label of font to apply on it
        /// @param position (default: 0 0) position to place
        /// @param origin (default: 0 0) origin of text (0 -> left or top 1 -> right ro down)
        /// @param character_size (default: 32) size of the text
        /// @param rotation (default: 0) rotation of the text
        /// @param text (defaule: New Text) content to display
        Text(const engine::ecs::Entity &entity, std::istream &data);

        /// @brief Destroy graphical resources
        void onDestroy();
    };
}
