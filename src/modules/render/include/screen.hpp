////////////////////////
//
//  Created on Mon Oct 09 2023
//
//  screen.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"
#include "math/vector2.hpp"

namespace render
{
    class RenderData;

    class Screen : public engine::Singleton<Screen>
    {
        public:
            Screen() = default;

            inline math::Vector2f getSize() const { return _size; }

            friend class RenderData;

        private:
            math::Vector2f _size;

            inline void setSize(const math::Vector2f &size) { _size = size; }
    };
}
