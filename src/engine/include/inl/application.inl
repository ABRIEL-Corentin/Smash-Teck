////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  application.inl
//
////////////////////////

#include "application.hpp"

namespace engine
{
    inline bool Application::isRunning() const
    {
        return m_is_running;
    }

    inline void Application::close()
    {
        m_is_running = false;
    }

    inline void Application::loadScene(const LoadingSceneRequest &request)
    {
        m_scene.requestLoadScene(request);
    }
}
