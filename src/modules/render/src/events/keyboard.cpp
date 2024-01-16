////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  keyboard.cpp
//
////////////////////////

#include "events/keyboard.hpp"
#include <SFML/Window.hpp>
#include "events/time.hpp"
#include <iostream>

namespace render
{
    std::array<Keyboard::KeyData, Keyboard::Key::KeyCount> Keyboard::_keys = std::array<Keyboard::KeyData, Keyboard::Key::KeyCount>();

    bool Keyboard::isKeyPressed(Key key)
    {
        return _keys.at(key).is_pressing;
    }

    bool Keyboard::isKeyPressedAsButton(Key key)
    {
        return _keys.at(key).is_pressing && !_keys.at(key).old_pressing;
    }

    bool Keyboard::isKeyReleased(Key key)
    {
        return !_keys.at(key).is_pressing;
    }

    bool Keyboard::isKeyReleasedAsButton(Key key, float &duration)
    {
        bool is_released = !_keys.at(key).is_pressing && _keys.at(key).old_pressing;

        if (is_released)
            duration = _keys.at(key).duration;

        return is_released;
    }

    bool Keyboard::isKeyReleasedAsButton(Key key)
    {
        return !_keys.at(key).is_pressing && _keys.at(key).old_pressing;
    }

    void Keyboard::update()
    {
        bool is_key_pressed = false;

        for (std::size_t i = 0; i < Key::KeyCount; ++i) {
            is_key_pressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));

            if (is_key_pressed)
                _keys.at(i).duration += Time::getInstance().getDeltaTime();

            if (is_key_pressed != _keys.at(i).is_pressing && is_key_pressed)
                _keys.at(i).duration = 0;

            _keys.at(i).old_pressing = _keys.at(i).is_pressing;
            _keys.at(i).is_pressing = is_key_pressed;
        }
    }
}
