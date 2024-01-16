////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  scene.inl
//
////////////////////////

#include "scene.hpp"

namespace engine
{
    inline void Scene::requestLoadScene(const LoadingSceneRequest &request)
    {
        m_requests_load_scenes.push_back(request);
    }
}
