////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  application.cpp
//
////////////////////////

#include "application.hpp"
#include "patterns.hpp"
#include <sstream>
#include <fstream>

namespace engine
{
    Application::Application()
        : m_world(ecs::World::getInstance()),
          m_scene(m_world),
          m_is_running(true)
    { }

    void Application::init()
    {
        m_scene.requestLoadScene(LoadingSceneRequest("./scene/scene.txt"));
    }

    void Application::launch()
    {
        while (m_is_running) {
            m_world.launchSystems();
            m_world.applyRequests();
            m_scene.applyRequests();
        }
    }
}
