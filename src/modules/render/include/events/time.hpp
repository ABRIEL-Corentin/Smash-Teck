////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  time.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"

namespace sf
{
    class Clock;
    class Time;
}

namespace render
{
    class RenderData;

    class Time : public engine::Singleton<Time>
    {
        public:
            Time() = default;

            inline float getDeltaTime() const { return _delta_time; }

            friend class RenderData;

        private:
            float _delta_time;

            void update();
    };
}
