////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  scene.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"
#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <functional>

namespace engine
{
    using LoadingSceneCallback = void (*)(const ecs::Entities &);
    using LoadingSceneArgs = std::vector<std::string>;

    using LoadingSceneRequest = struct LoadingSceneRequest
    {
        std::string file_name;
        LoadingSceneArgs args;
        LoadingSceneCallback callback;

        LoadingSceneRequest(const std::string &file_name, const LoadingSceneArgs &args = LoadingSceneArgs(), LoadingSceneCallback callback = nullptr);
    };

    class Scene
    {
        public:
            Scene(ecs::World &world);

            inline void requestLoadScene(const LoadingSceneRequest &request);
            void applyRequests();

        private:
            ecs::World &m_world;
            std::vector<LoadingSceneRequest> m_requests_load_scenes;

            ecs::Entities loadScene(const std::string &file_name, const std::vector<std::string> &args = std::vector<std::string>());
            ecs::Entities generateEntities(const std::string &scene, const std::string &file_name);
            void applyArgs(std::string &scene, const std::vector<std::string> &args);
            void calculateArgs(std::string &scene);
            std::string calculate(const std::string &calculus);
            std::size_t getArgLength(const std::string &scene, std::size_t start);
            std::string trimString(const std::string &str);
            std::vector<std::string> splitStr(const std::string &str);
    };
}

#include "inl/scene.inl"
