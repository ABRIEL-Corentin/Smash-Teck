////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  render_data.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"
#include "application.hpp"
#include "math/vector2.hpp"
#include "math/color.hpp"
#include "utils.hpp"
#include "screen.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace render
{
    class RenderData : public engine::Singleton<RenderData>
    {
        public:
            RenderData();

            // Animations
            std::size_t getAnimationID(const std::string &animation_label);
            std::vector<std::size_t> getAnimation(const std::string &animation_label);
            std::vector<std::size_t> getAnimation(std::size_t id);

            // Shapes
            std::size_t getTextureID(const std::string &texture_label) const;
            std::string getTextureLabel(std::size_t texture_id) const;
            std::size_t generateShapeWithTexture(const std::string &texture_label);
            std::size_t generateShapeWithTexture(std::size_t texture_id);
            void destroyShape(std::size_t id);
            void shapeSetTexture(std::size_t id, const std::string &texture_label);
            void shapeSetTexture(std::size_t id, std::size_t texture_id);
            math::Color shapeGetColor(std::size_t id) const;
            void shapeSetColor(std::size_t id, const math::Color &color);
            math::Vector2f shapeGetSize(std::size_t id) const;
            void shapeSetSize(std::size_t id, const math::Vector2f &size);
            math::Vector2f shapeGetPosition(std::size_t id) const;
            void shapeSetPosition(std::size_t id, const math::Vector2f &position);
            void shapeMove(std::size_t id, const math::Vector2f &offset);
            float shapeGetRotation(std::size_t id) const;
            void shapeSetRotation(std::size_t id, float angle);
            void shapeRotate(std::size_t id, float angle);

            // Texts
            std::size_t getFontID(const std::string &font_label) const;
            std::size_t generateTextWithFont(const std::string &font_label);
            std::size_t generateTextWithFont(std::size_t font_id);
            void destroyText(std::size_t id);
            std::size_t textSetFont(std::size_t id, const std::string &font_label);
            std::size_t textSetFont(std::size_t id, std::size_t font_id);
            math::Color textGetColor(std::size_t id) const;
            void textSetColor(std::size_t id, const math::Color &color);
            math::Vector2f textGetSize(std::size_t id) const;
            std::size_t textGetCharacterSize(std::size_t id) const;
            void textSetCharacterSize(std::size_t id, std::size_t size);
            math::Vector2f textGetPosition(std::size_t id) const;
            void textSetPosition(std::size_t id, const math::Vector2f &position);
            math::Vector2f textGetOrigin(std::size_t id) const;
            void textSetOrigin(std::size_t id, const math::Vector2f &origin);
            void textMove(std::size_t id, const math::Vector2f &offset);
            float textGetRotation(std::size_t id) const;
            void textSetRotation(std::size_t id, float angle);
            void textRotate(std::size_t id, float angle);
            std::string textGetStr(std::size_t id) const;
            void textSetStr(std::size_t id, const std::string &str);

            // Sounds
            std::size_t getSoundBufferID(const std::string &sound_buffer_label) const;
            std::size_t generateSoundWithSoundBuffer(const std::string &sound_buffer_label);
            std::size_t generateSoundWithSoundBuffer(std::size_t sound_buffer_id);
            void destroySound(std::size_t id);
            std::size_t soundSetSoundBuffer(std::size_t id, const std::string &sound_buffer_label);
            std::size_t soundSetSoundBuffer(std::size_t id, std::size_t sound_buffer_id);
            void soundPlay(std::size_t id);
            void soundPause(std::size_t id);
            void soundStop(std::size_t id);
            bool soundGetLoop(std::size_t id) const;
            void soundSetLoop(std::size_t id, bool loop);
            float soundGetVolume(std::size_t id) const;
            void soundSetVolume(std::size_t id, float volume);

            // Musics

            // Render
            void renderShape(std::size_t id);
            void renderText(std::size_t id);
            void update();
            math::Vector2f getScreenSize() const;

        private:
            sf::RenderWindow m_window;

            // Animations
            std::vector<std::pair<std::string, std::vector<std::size_t>>> m_animations;

            // Shapes
            std::vector<std::pair<std::string, sf::Texture>> m_textures;
            std::vector<std::optional<sf::RectangleShape>> m_shapes;
            std::size_t m_current_shape_id;
            std::vector<std::size_t> m_available_shapes;

            // Texts
            std::vector<std::pair<std::string, sf::Font>> m_fonts;
            std::vector<std::optional<sf::Text>> m_texts;
            std::size_t m_current_text_id;
            std::vector<std::size_t> m_available_texts;

            // Sounds
            std::vector<std::pair<std::string, sf::SoundBuffer>> _sounds_buffers;
            std::vector<std::optional<sf::Sound>> _sounds;
            std::size_t _current_sound_id;
            std::vector<std::size_t> _available_sounds;

            void pollEvents();
            void loadResources();
            void loadAnimateTexture(const std::string &name, const std::string &file_name, const sf::Vector2i &nbr_of_sprite, const sf::Vector2i &position, const sf::Vector2i &size);
            void loadTexture(const std::string &texture_label, const std::string &file_name, const sf::IntRect &area = sf::IntRect());
            void loadFont(const std::string &font_label, const std::string &file_name);
            void loadSoundBuffer(const std::string &sound_buffer_label, const std::string &file_name);
            void generateAnimation(const std::string &animation_label, const std::vector<std::string> &textures_labels);
    };
}
