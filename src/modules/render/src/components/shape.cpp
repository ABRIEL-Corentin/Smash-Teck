////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  shape.cpp
//
////////////////////////

#include "components/shape.hpp"
#include "render_data.hpp"

namespace render
{
    Shape::Shape(const engine::ecs::Entity &, std::istream &data)
    {
        std::string texture_label = std::string();
        math::Vector2f position = math::Vector2f();
        math::Vector2f size = math::Vector2f(100, 100);
        float rotation = 0;

        data >> texture_label;
        data >> position;
        data >> size;
        data >> rotation;

        texture_id = RenderData::getInstance().getTextureID(texture_label);
        id = RenderData::getInstance().generateShapeWithTexture(texture_id);

        setPosition(position);
        setRotation(rotation);
        setSize(size);
    }

    void Shape::onDestroy()
    {
        RenderData::getInstance().destroyShape(id);
    }

    void Shape::setTexture(const std::string &texture_label)
    {
        RenderData::getInstance().shapeSetTexture(id, texture_label);
    }

    void Shape::setTexture(std::size_t texture_id)
    {
        RenderData::getInstance().shapeSetTexture(id, texture_id);
    }

    math::Color Shape::getColor() const
    {
        return RenderData::getInstance().shapeGetColor(id);
    }

    void Shape::setColor(const math::Color &color)
    {
        RenderData::getInstance().shapeSetColor(id, color);
    }

    math::Vector2f Shape::getSize() const
    {
        return RenderData::getInstance().shapeGetSize(id);
    }

    void Shape::setSize(const math::Vector2f &size)
    {
        RenderData::getInstance().shapeSetSize(id, size);
    }

    void Shape::setSize(float width, float height)
    {
        setSize({width, height});
    }

    math::Vector2f Shape::getScale() const
    {
        return RenderData::getInstance().shapeGetScale(id);
    }

    void Shape::setScale(const math::Vector2f &scale)
    {
        RenderData::getInstance().shapeSetScale(id, scale);
    }

    void Shape::setScale(float width, float height)
    {
        setScale({width, height});
    }

    math::Vector2f Shape::getPosition() const
    {
        return RenderData::getInstance().shapeGetPosition(id);
    }

    void Shape::setPosition(const math::Vector2f &position)
    {
        RenderData::getInstance().shapeSetPosition(id, position);
    }

    void Shape::setPosition(float x, float y)
    {
        setPosition({x, y});
    }

    void Shape::move(const math::Vector2f &offset)
    {
        RenderData::getInstance().shapeMove(id, offset);
    }

    void Shape::move(float x, float y)
    {
        move({x, y});
    }

    math::Rectf Shape::getRect() const
    {
        return math::Rectf(getPosition(), getSize());
    }

    void Shape::setRect(const math::Rectf &rect)
    {
        setPosition(rect.left, rect.top);
        setSize(rect.width, rect.height);
    }

    float Shape::getRotation() const
    {
        return RenderData::getInstance().shapeGetRotation(id);
    }

    void Shape::setRotation(float angle)
    {
        RenderData::getInstance().shapeSetRotation(id, angle);
    }

    void Shape::rotate(float angle)
    {
        RenderData::getInstance().shapeRotate(id, angle);
    }
}
