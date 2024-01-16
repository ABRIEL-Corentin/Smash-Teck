////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  test_system.cpp
//
////////////////////////

#include "systems/test_system.hpp"
#include "ecs/world.hpp"
#include "application.hpp"
#include "time.h"

void testSystem()
{
    std::cout << "System Call" << std::endl;
    sleep(1);
    engine::Application::getInstance().close();
}
