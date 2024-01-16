////////////////////////
//
//  Created on Mon Oct 30 2023
//
//  sound.cpp
//
////////////////////////

#include "components/sound.hpp"
#include "render_data.hpp"

namespace render
{
    Sound::Sound(const engine::ecs::Entity &, std::istream &data)
    {
        std::string sound_buffer_label = std::string();
        float volume = 10;
        bool loop = false;

        data >> sound_buffer_label;
        data >> volume;
        data >> loop;

        sound_buffer_id = RenderData::getInstance().getSoundBufferID(sound_buffer_label);
        id = RenderData::getInstance().generateSoundWithSoundBuffer(sound_buffer_id);

        setLoop(loop);
        setVolume(volume);
        play();
    }

    void Sound::onDestroy()
    {
        RenderData::getInstance().destroySound(id);
    }

    void Sound::play()
    {
        RenderData::getInstance().soundPlay(id);
    }

    void Sound::pause()
    {
        RenderData::getInstance().soundPause(id);
    }

    void Sound::stop()
    {
        RenderData::getInstance().soundStop(id);
    }

    bool Sound::getLoop() const
    {
        return RenderData::getInstance().soundGetLoop(id);
    }

    void Sound::setLoop(bool loop)
    {
        RenderData::getInstance().soundSetLoop(id, loop);
    }

    float Sound::getVolume() const
    {
        return RenderData::getInstance().soundGetVolume(id);
    }

    void Sound::setVolume(float volume)
    {
        RenderData::getInstance().soundSetVolume(id, volume);
    }
}
