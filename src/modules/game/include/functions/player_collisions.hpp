////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player_collisions.hpp
//
////////////////////////

#pragma once

#include "components/collision.hpp"

namespace game
{
    void onPlayerCollisionStay(render::CollisionBox &box, render::CollisionBox &other);
}
