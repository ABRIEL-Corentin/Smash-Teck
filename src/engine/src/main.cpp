////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  main.cpp
//
////////////////////////

#include <iostream>
#include "ecs/world.hpp"
#include "application.hpp"
#include "config.hpp"

int main(int argc, char **argv)
{

    engine::Application &app = engine::Application::getInstance();
    engine::Config &config = engine::Config::getInstance();

    if (config.loadArgs(argc, argv))
        return 84;
    app.init();
    app.launch();
    return 0;
}
