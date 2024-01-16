////////////////////////
//
//  Created on Wed Sep 27 2023
//
//  text.cpp
//
////////////////////////

#include "components/text.hpp"
#include "render_data.hpp"

namespace render
{
    Text::Text(const engine::ecs::Entity &, std::istream &data)
    {
        std::string font_label = std::string();
        math::Vector2f position = math::Vector2f();
        math::Vector2f origin = math::Vector2f();
        float character_size = 32;
        float rotation = 0;
        std::string str = std::string();
        std::string word = std::string();

        data >> font_label;
        data >> position;
        data >> origin;
        data >> character_size;
        data >> rotation;

        while (data >> word)
            str += word + " ";

        if (str.size())
            str.pop_back();
        else
            str = "New Text";

        font_id = RenderData::getInstance().getFontID(font_label);
        id = RenderData::getInstance().generateTextWithFont(font_id);

        setCharacterSize(character_size);
        setStr(str);
        setOrigin(origin);
        setPosition(position);
        setRotation(rotation);
    }

    void Text::onDestroy()
    {
        RenderData::getInstance().destroyText(id);
    }

    void Text::setFont(const std::string &font_label)
    {
        font_id = RenderData::getInstance().textSetFont(id, font_label);
    }

    void Text::setFont(std::size_t font_id)
    {
        font_id = RenderData::getInstance().textSetFont(id, font_id);
    }

    math::Color Text::getColor() const
    {
        return RenderData::getInstance().textGetColor(id);
    }

    void Text::setColor(const math::Color &color)
    {
        RenderData::getInstance().textSetColor(id, color);
    }

    math::Vector2f Text::getSize() const
    {
        return RenderData::getInstance().textGetSize(id);
    }

    std::size_t Text::getCharacterSize() const
    {
        return RenderData::getInstance().textGetCharacterSize(id);
    }

    void Text::setCharacterSize(std::size_t size)
    {
        RenderData::getInstance().textSetCharacterSize(id, size);
    }

    math::Vector2f Text::getPosition() const
    {
        return RenderData::getInstance().textGetPosition(id);
    }

    void Text::setPosition(const math::Vector2f &position)
    {
        RenderData::getInstance().textSetPosition(id, position);
    }

    math::Vector2f Text::getOrigin() const
    {
        return RenderData::getInstance().textGetOrigin(id);
    }

    void Text::setOrigin(const math::Vector2f &origin)
    {
        RenderData::getInstance().textSetOrigin(id, origin);
    }

    void Text::move(const math::Vector2f &offset)
    {
        RenderData::getInstance().textMove(id, offset);
    }

    float Text::getRotation() const
    {
        return RenderData::getInstance().textGetRotation(id);
    }

    void Text::setRotation(float angle)
    {
        RenderData::getInstance().textSetRotation(id, angle);
    }

    void Text::rotate(float angle)
    {
        RenderData::getInstance().textRotate(id, angle);
    }

    std::string Text::getStr() const
    {
        return RenderData::getInstance().textGetStr(id);
    }

    void Text::setStr(const std::string &str)
    {
        RenderData::getInstance().textSetStr(id, str);
    }
}
