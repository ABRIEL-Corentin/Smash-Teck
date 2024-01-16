////////////////////////
//
//  Created on Tue Sep 19 2023
//
//  application.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"
#include "singleton.hpp"
#include "scene.hpp"

int main(int argc, char **argv);

namespace engine
{
    class Application : public Singleton<Application>
    {
        public:
            Application();

            inline bool isRunning() const;
            inline void close();
            inline void loadScene(const LoadingSceneRequest &request);

            friend int ::main(int argc, char **argv);

        private:
            ecs::World &m_world;
            Scene m_scene;
            bool m_is_running;

            void init();
            void launch();
    };
}

#include "inl/application.inl"
