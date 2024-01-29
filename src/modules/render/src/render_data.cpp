////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  render_data.cpp
//
////////////////////////

#include "render_data.hpp"
#include "events/time.hpp"
#include "events/keyboard.hpp"
#include <iostream>

#define SHOW_BORDER -5

namespace render
{
    RenderData::RenderData()
        : m_window({1920, 1080}, "Smash Teck"),
          m_animations(),
          m_textures(),
          m_shapes(),
          m_current_shape_id(0),
          m_available_shapes(),
          m_fonts(),
          m_texts(),
          m_current_text_id(0),
          m_available_texts()
    {
        m_window.setVerticalSyncEnabled(true);
        loadResources();
        Screen::getInstance().setSize(math::Vector2f(m_window.getSize().x, m_window.getSize().y));
    }

    std::size_t RenderData::getAnimationID(const std::string &animation_label)
    {
        for (std::size_t i = 0; i < m_animations.size(); ++i)
            if (m_animations.at(i).first == animation_label)
                return i;

        std::cerr << "Failed to get animation id from label: '" << animation_label << "'" << std::endl;
        return 0;
    }

    std::vector<std::size_t> RenderData::getAnimation(const std::string &animation_label)
    {
        for (auto animation = m_animations.begin(); animation != m_animations.end(); ++animation)
            if (animation->first == animation_label)
                return animation->second;

        std::cerr << "Failed to get animation from label: '" << animation_label << "'" << std::endl;
        return std::vector<std::size_t>();
    }

    std::vector<std::size_t> RenderData::getAnimation(std::size_t id)
    {
        if (id >= m_animations.size()) {
            std::cerr << "Failed to get animation from id: " << id << std::endl;
            return std::vector<std::size_t>();
        }

        return m_animations.at(id).second;
    }

    std::size_t RenderData::getTextureID(const std::string &texture_label) const
    {
        for (std::size_t i = 0; i < m_textures.size(); ++i)
            if (m_textures.at(i).first == texture_label)
                return i;

        std::cerr << "Failed to get texture id from label: '" << texture_label << "'" << std::endl;
        return 0;
    }

    std::string RenderData::getTextureLabel(std::size_t texture_id) const
    {
        if (texture_id >= m_textures.size()) {
            std::cerr << "Failed to get texture label from id: " << texture_id << std::endl;
            return std::string();
        }

        return m_textures.at(texture_id).first;
    }

    std::size_t RenderData::generateShapeWithTexture(const std::string &texture_label)
    {
        std::size_t texture_id = getTextureID(texture_label);
        std::size_t shape_id = 0;
        sf::RectangleShape shape = sf::RectangleShape();

        shape.setTexture(&m_textures.at(texture_id).second);

        #ifdef SHOW_BORDER
            shape.setOutlineColor(sf::Color::Red);
            shape.setOutlineThickness(SHOW_BORDER);
        #endif

        if (m_available_shapes.size()) {
            shape_id = m_available_shapes.front();
            m_available_shapes.erase(m_available_shapes.begin());
        } else
            shape_id = m_current_shape_id++;

        if (m_shapes.size() <= shape_id)
            m_shapes.resize(shape_id + 1);

        m_shapes.at(shape_id).emplace(shape);

        if (texture_label == "blank")
            m_shapes.back()->setFillColor(sf::Color::Transparent);

        return shape_id;
    }

    std::size_t RenderData::generateShapeWithTexture(std::size_t texture_id)
    {
        std::size_t shape_id = 0;
        sf::RectangleShape shape = sf::RectangleShape();

        shape.setTexture(&m_textures.at(texture_id).second);

        #ifdef SHOW_BORDER
            shape.setOutlineColor(sf::Color::Red);
            shape.setOutlineThickness(SHOW_BORDER);
        #endif

        if (m_available_shapes.size()) {
            shape_id = m_available_shapes.front();
            m_available_shapes.erase(m_available_shapes.begin());
        } else
            shape_id = m_current_shape_id++;

        if (m_shapes.size() <= shape_id)
            m_shapes.resize(shape_id + 1);

        m_shapes.at(shape_id).emplace(shape);

        if (getTextureLabel(texture_id) == "blank")
            m_shapes.back()->setFillColor(sf::Color::Transparent);

        return shape_id;
    }

    void RenderData::destroyShape(std::size_t id)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt)
            return;

        m_shapes.at(id).reset();
        m_available_shapes.push_back(id);
    }

    void RenderData::shapeSetTexture(std::size_t id, const std::string &texture_label)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to update texture from label '" << texture_label << "' for shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setTexture(&m_textures.at(getTextureID(texture_label)).second);
    }

    void RenderData::shapeSetTexture(std::size_t id, std::size_t texture_id)
    {
        if (m_shapes.size() <= id || m_textures.size() <= texture_id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to update texture from id '" << texture_id << "' for shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setTexture(&m_textures.at(texture_id).second);
    }

    math::Color RenderData::shapeGetColor(std::size_t id) const
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to get color of shape " << id << std::endl;
            return math::Color();
        }

        sf::Color color = m_shapes.at(id)->getFillColor();
        return math::Color(color.r, color.g, color.b, color.a);
    }

    void RenderData::shapeSetColor(std::size_t id, const math::Color &color)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to set color of shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    }

    math::Vector2f RenderData::shapeGetSize(std::size_t id) const
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to get size of shape " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2f(m_shapes.at(id)->getSize().x, m_shapes.at(id)->getSize().y);
    }

    void RenderData::shapeSetSize(std::size_t id, const math::Vector2f &size)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to update size of shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setSize({size.x, size.y});
        m_shapes.at(id)->setOrigin({size.x / 2, size.y / 2});
    }

    math::Vector2f RenderData::shapeGetScale(std::size_t id) const
    {
        if (m_shapes.size() <= id || !m_shapes.at(id).has_value()) {
            std::cerr << "Failed to get scale of shape " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2f(m_shapes.at(id)->getScale().x, m_shapes.at(id)->getScale().y);
    }

    void RenderData::shapeSetScale(std::size_t id, const math::Vector2f &scale)
    {
        if (m_shapes.size() <= id || !m_shapes.at(id).has_value()) {
            std::cout << "Failed to update scale of shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setScale(scale.x, scale.y);
    }

    math::Vector2f RenderData::shapeGetPosition(std::size_t id) const
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to get position of shape " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2(m_shapes.at(id)->getPosition().x, m_shapes.at(id)->getPosition().y);
    }

    void RenderData::shapeSetPosition(std::size_t id, const math::Vector2f &position)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to set position of shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setPosition({position.x, position.y});
    }

    void RenderData::shapeMove(std::size_t id, const math::Vector2f &offset)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to move shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->move({offset.x, offset.y});
    }

    float RenderData::shapeGetRotation(std::size_t id) const
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to get rotation of shape " << id << std::endl;
            return 0;
        }

        return m_shapes.at(id)->getRotation();
    }

    void RenderData::shapeSetRotation(std::size_t id, float angle)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to set rotation of shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->setRotation(angle);
    }

    void RenderData::shapeRotate(std::size_t id, float angle)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to rotate shape " << id << std::endl;
            return;
        }

        m_shapes.at(id)->rotate(angle);
    }

    std::size_t RenderData::getFontID(const std::string &font_label) const
    {
        for (std::size_t i = 0; i < m_fonts.size(); ++i)
            if (m_fonts.at(i).first == font_label)
                return i;

        std::cerr << "Failed to get font id from label: '" << font_label << "'" << std::endl;
        return 0;
    }

    std::size_t RenderData::generateTextWithFont(const std::string &font_label)
    {
        return generateTextWithFont(getFontID(font_label));
    }

    std::size_t RenderData::generateTextWithFont(std::size_t font_id)
    {
        std::size_t text_id = 0;
        sf::Text text = sf::Text();

        if (m_fonts.size() <= font_id) {
            std::cerr << "Failed to generate text with font id: " << font_id << std::endl;
            return 0;
        }

        text.setFont(m_fonts.at(font_id).second);

        if (m_available_texts.size()) {
            text_id = m_available_texts.front();
            m_available_texts.erase(m_available_texts.begin());
        } else
            text_id = m_current_text_id++;

        if (m_texts.size() <= text_id)
            m_texts.resize(text_id + 1);

        m_texts.at(text_id).emplace(text);
        return text_id;
    }

    void RenderData::destroyText(std::size_t id)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt)
            return;

        m_texts.at(id).reset();
        m_available_texts.push_back(id);
    }

    std::size_t RenderData::textSetFont(std::size_t id, const std::string &font_label)
    {
        std::size_t font_id = getFontID(font_label);

        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt || m_fonts.size() <= font_id) {
            std::cerr << "Failed to set text font " << id << std::endl;
            return font_id;
        }

        m_texts.at(id)->setFont(m_fonts.at(font_id).second);
        return font_id;
    }

    std::size_t RenderData::textSetFont(std::size_t id, std::size_t font_id)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt || m_fonts.size() <= font_id) {
            std::cerr << "Failed to set text font " << id << std::endl;
            return font_id;
        }

        m_texts.at(id)->setFont(m_fonts.at(font_id).second);
        return font_id;
    }

    math::Color RenderData::textGetColor(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text color " << id << std::endl;
            return math::Color();
        }

        sf::Color color = m_texts.at(id)->getFillColor();
        return math::Color(color.r, color.g, color.b, color.a);
    }

    void RenderData::textSetColor(std::size_t id, const math::Color &color)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text color " << id << std::endl;
            return;
        }

        m_texts.at(id)->setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    }

    math::Vector2f RenderData::textGetSize(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text size " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2f(m_texts.at(id)->getLocalBounds().width, m_texts.at(id)->getLocalBounds().height);
    }

    std::size_t RenderData::textGetCharacterSize(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text character size " << id << std::endl;
            return 0;
        }

        return m_texts.at(id)->getCharacterSize();
    }

    void RenderData::textSetCharacterSize(std::size_t id, std::size_t size)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text character size " << id << std::endl;
            return;
        }

        m_texts.at(id)->setCharacterSize(size);
    }

    math::Vector2f RenderData::textGetPosition(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text position " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2f(m_texts.at(id)->getPosition().x, m_texts.at(id)->getPosition().y);
    }

    void RenderData::textSetPosition(std::size_t id, const math::Vector2f &position)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text position " << id << std::endl;
            return;
        }

        m_texts.at(id)->setPosition({position.x, position.y});
    }

    math::Vector2f RenderData::textGetOrigin(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text origin " << id << std::endl;
            return math::Vector2f();
        }

        return math::Vector2f(
            m_texts.at(id)->getOrigin().x / m_texts.at(id)->getLocalBounds().width,
            m_texts.at(id)->getOrigin().y / m_texts.at(id)->getLocalBounds().height
        );
    }

    void RenderData::textSetOrigin(std::size_t id, const math::Vector2f &origin)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text origin " << id << std::endl;
            return;
        }

        m_texts.at(id)->setOrigin(sf::Vector2f(
            m_texts.at(id)->getLocalBounds().width * origin.x,
            m_texts.at(id)->getLocalBounds().height * origin.y
        ));
    }

    void RenderData::textMove(std::size_t id, const math::Vector2f &offset)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to move text " << id << std::endl;
            return;
        }

        m_texts.at(id)->move({offset.x, offset.y});
    }

    float RenderData::textGetRotation(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text rotation " << id << std::endl;
            return 0;
        }

        return m_texts.at(id)->getRotation();
    }

    void RenderData::textSetRotation(std::size_t id, float angle)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text rotation " << id << std::endl;
            return;
        }

        m_texts.at(id)->setRotation(angle);
    }

    void RenderData::textRotate(std::size_t id, float angle)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to rotate text " << id << std::endl;
            return;
        }

        m_texts.at(id)->rotate(angle);
    }

    std::string RenderData::textGetStr(std::size_t id) const
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to get text str " << id << std::endl;
            return std::string();
        }

        return m_texts.at(id)->getString();
    }

    void RenderData::textSetStr(std::size_t id, const std::string &str)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to set text str " << id << std::endl;
            return;
        }

        m_texts.at(id)->setString(str);
    }

    std::size_t RenderData::getSoundBufferID(const std::string &sound_buffer_label) const
    {
        for (std::size_t i = 0; i < _sounds_buffers.size(); ++i)
            if (_sounds_buffers.at(i).first == sound_buffer_label)
                return i;

        std::cerr << "Failed to get sound buffer id from label: " << sound_buffer_label << std::endl;
        return 0;
    }

    std::size_t RenderData::generateSoundWithSoundBuffer(const std::string &sound_buffer_label)
    {
        return generateSoundWithSoundBuffer(getSoundBufferID(sound_buffer_label));
    }

    std::size_t RenderData::generateSoundWithSoundBuffer(std::size_t sound_buffer_id)
    {
        std::size_t sound_id = 0;
        sf::Sound sound = sf::Sound();

        if (_sounds_buffers.size() <= sound_buffer_id) {
            std::cerr << "Failed to generate sound with sound buffer id: " << sound_buffer_id << std::endl;
            return 0;
        }

        sound.setBuffer(_sounds_buffers.at(sound_buffer_id).second);

        if (_available_sounds.size()) {
            sound_id = _available_sounds.front();
            _available_sounds.erase(_available_sounds.begin());
        } else
            sound_id = _current_sound_id++;

        if (_sounds.size() <= sound_id)
            _sounds.resize(sound_id + 1);

        _sounds.at(sound_id).emplace(sound);
        return sound_id;
    }

    void RenderData::destroySound(std::size_t id)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt)
            return;

        _sounds.at(id).reset();
        _available_sounds.push_back(id);
    }

    std::size_t RenderData::soundSetSoundBuffer(std::size_t id, const std::string &sound_buffer_label)
    {
        std::size_t sound_buffer_id = getSoundBufferID(sound_buffer_label);

        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to set sound buffer " << id << std::endl;
            return sound_buffer_id;
        }

        _sounds.at(id)->setBuffer(_sounds_buffers.at(sound_buffer_id).second);
        return sound_buffer_id;
    }

    std::size_t RenderData::soundSetSoundBuffer(std::size_t id, std::size_t sound_buffer_id)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to set sound buffer " << id << std::endl;
            return sound_buffer_id;
        }

        _sounds.at(id)->setBuffer(_sounds_buffers.at(sound_buffer_id).second);
        return sound_buffer_id;
    }

    void RenderData::soundPlay(std::size_t id)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to play sound " << id << std::endl;
            return;
        }

        _sounds.at(id)->play();
    }

    void RenderData::soundPause(std::size_t id)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to pause sound " << id << std::endl;
            return;
        }

        _sounds.at(id)->pause();
    }

    void RenderData::soundStop(std::size_t id)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to stop sound " << id << std::endl;
            return;
        }

        _sounds.at(id)->stop();
    }

    bool RenderData::soundGetLoop(std::size_t id) const
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to get sound loop " << id << std::endl;
            return false;
        }

        return _sounds.at(id)->getLoop();
    }

    void RenderData::soundSetLoop(std::size_t id, bool loop)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to set sound loop " << id << std::endl;
            return;
        }

        _sounds.at(id)->setLoop(loop);
    }

    float RenderData::soundGetVolume(std::size_t id) const
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to get sound volume " << id << std::endl;
            return 0;
        }

        return _sounds.at(id)->getVolume();
    }

    void RenderData::soundSetVolume(std::size_t id, float volume)
    {
        if (_sounds.size() <= id || _sounds.at(id) == std::nullopt) {
            std::cerr << "Failed to set sound volume " << id << std::endl;
            return;
        }

        _sounds.at(id)->setVolume(volume);
    }

    void RenderData::renderShape(std::size_t id)
    {
        if (m_shapes.size() <= id || m_shapes.at(id) == std::nullopt) {
            std::cerr << "Failed to draw shape " << id << std::endl;
            return;
        }

        m_window.draw(m_shapes.at(id).value());
    }

    void RenderData::renderText(std::size_t id)
    {
        if (m_texts.size() <= id || m_texts.at(id) == std::nullopt) {
            std::cerr << "Failed to draw text " << id << std::endl;
            return;
        }

        m_window.draw(m_texts.at(id).value());
    }

    void RenderData::update()
    {
        m_window.display();
        m_window.clear();

        Time::getInstance().update();
        Keyboard::update();
        pollEvents();
    }

    math::Vector2f RenderData::getScreenSize() const
    {
        return math::Vector2f(m_window.getSize().x, m_window.getSize().y);
    }

    void RenderData::pollEvents()
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    engine::Application::getInstance().close();
                    break;
                default:
                    break;
            }
        }
    }

    void RenderData::loadResources()
    {
        loadTexture("blank", "./source/blank.png");
        loadAnimateTexture("piranha_plant_idle", "./source/piranha-plant-idle-Sheet.png", {6, 1}, {0, 0}, {64, 64});
        generateAnimation("piranha_plant_idle", {
            "piranha_plant_idle_1",
            "piranha_plant_idle_2",
            "piranha_plant_idle_3",
            "piranha_plant_idle_4",
            "piranha_plant_idle_5",
            "piranha_plant_idle_6",
        });
        loadAnimateTexture("piranha_plant_attack", "./source/piranha-plant-attack-Sheet.png", {11, 1}, {0, 0}, {64, 64});
        generateAnimation("piranha_plant_attack", {
            "piranha_plant_attack_1",
            "piranha_plant_attack_2",
            "piranha_plant_attack_3",
            "piranha_plant_attack_4",
            "piranha_plant_attack_5",
            "piranha_plant_attack_6",
            "piranha_plant_attack_7",
            "piranha_plant_attack_8",
            "piranha_plant_attack_9",
            "piranha_plant_attack_10",
            "piranha_plant_attack_11",
        });
        loadAnimateTexture("piranha_plant_running", "./source/piranha-plant-running-Sheet.png", {6, 1}, {0, 0}, {64, 64});
        generateAnimation("piranha_plant_running", {
            "piranha_plant_running_1",
            "piranha_plant_running_2",
            "piranha_plant_running_3",
            "piranha_plant_running_4",
            "piranha_plant_running_5",
            "piranha_plant_running_6",
        });
        loadAnimateTexture("piranha_plant_jump", "./source/piranha-plant-jump-Sheet.png", {4, 1}, {0, 0}, {64, 64});
        generateAnimation("piranha_plant_jump", {
            "piranha_plant_jump_1",
            "piranha_plant_jump_2",
            "piranha_plant_jump_3",
            "piranha_plant_jump_4",
        });
    }

    void RenderData::loadAnimateTexture(const std::string &name, const std::string &file_name, const sf::Vector2i &nbr_of_sprite, const sf::Vector2i &position, const sf::Vector2i &size)
    {
        std::string tmp_name = name;

        for (int y = 1; y <= nbr_of_sprite.y; ++y) {
            for (int x = 1; x <= nbr_of_sprite.x; ++x) {
                tmp_name = name;
                tmp_name.append("_");
                tmp_name.append(std::to_string(nbr_of_sprite.x * (y - 1) + x));
                loadTexture(tmp_name, file_name, {position.x + (size.x) * (x - 1), position.y + (size.y) * (y - 1), size.x, size.y});
            }
        }
    }

    void RenderData::loadTexture(const std::string &texture_label, const std::string &file_name, const sf::IntRect &area)
    {
        sf::Texture texture = sf::Texture();

        texture.loadFromFile(file_name, area);
        m_textures.push_back({texture_label, texture});
    }

    void RenderData::loadFont(const std::string &font_label, const std::string &file_name)
    {
        sf::Font font = sf::Font();

        font.loadFromFile(file_name);
        m_fonts.push_back({font_label, font});
    }

    void RenderData::loadSoundBuffer(const std::string &sound_buffer_label, const std::string &file_name)
    {
        sf::SoundBuffer sound_buffer = sf::SoundBuffer();

        sound_buffer.loadFromFile(file_name);
        _sounds_buffers.push_back({sound_buffer_label, sound_buffer});
    }

    void RenderData::generateAnimation(const std::string &animation_label, const std::vector<std::string> &textures_labels)
    {
        std::vector<std::size_t> textures_ids = std::vector<std::size_t>();

        for (auto texture_label = textures_labels.begin(); texture_label != textures_labels.end(); ++texture_label)
            textures_ids.push_back(getTextureID(*texture_label));

        m_animations.push_back({animation_label, textures_ids});
    }
}
