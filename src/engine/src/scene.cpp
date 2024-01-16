////////////////////////
//
//  Created on Tue Sep 26 2023
//
//  scene.cpp
//
////////////////////////

#include "scene.hpp"
#include "application.hpp"
#include "patterns.hpp"
#include "config.hpp"
#include <muParser.h>

namespace engine
{
    LoadingSceneRequest::LoadingSceneRequest(const std::string &file_name, const LoadingSceneArgs &args, LoadingSceneCallback callback)
        : file_name(file_name),
            args(args),
            callback(callback)
    { }

    Scene::Scene(ecs::World &world)
        : m_world(world),
          m_requests_load_scenes()
    { }

    void Scene::applyRequests()
    {
        for (auto request = m_requests_load_scenes.begin(); request != m_requests_load_scenes.end(); ++request) {
            if (request->callback)
                request->callback(loadScene(request->file_name, request->args));
            else
                loadScene(request->file_name, request->args);
        }

        m_requests_load_scenes.clear();
    }

    ecs::Entities Scene::loadScene(const std::string &file_name, const std::vector<std::string> &args)
    {
        std::ifstream ifs = std::ifstream(file_name);
        std::stringstream ss = std::stringstream();
        std::string scene = std::string();

        #if DEBUG_DISPLAY_SCENE_LOADING
            std::cout << "Loading scene at: " << file_name << std::endl;
        #endif

        if (!ifs.is_open()) {
            std::cerr << "Failed to open file at: " << file_name << std::endl;
            Application::getInstance().close();
            return ecs::Entities();
        }

        ss << ifs.rdbuf();
        scene = ss.str();

        applyArgs(scene, args);
        calculateArgs(scene);
        return generateEntities(scene, file_name);
    }

    ecs::Entities Scene::generateEntities(const std::string &scene, const std::string &file_name)
    {
        std::stringstream ss = std::stringstream(scene);
        std::string line = std::string();
        std::size_t line_index = 0;
        ecs::Entity entity = 0;
        ecs::Entities entities = ecs::Entities();
        bool is_components = false;

        while (std::getline(ss, line)) {
            ++line_index;
            line = line.substr(0, line.find('#'));
            line = trimString(line);

            if (!line.size())
                continue;
            else if (line == "ENTITY") {
                entity = m_world.createEntity();
                entities.push_back(entity);
                is_components = true;
                continue;
            } else if (line == "SYSTEM") {
                is_components = false;
                continue;
            }

            if (line.substr(0, line.find(' ')) == "LOAD_SCENE") {
                if (line.substr(line.find(' ') + 1, line.size() - line.find(' ')) == file_name) {
                    std::cerr << "Error infinite inclusion detected at line " << line_index << " on file: " << file_name << std::endl;
                    Application::getInstance().close();
                    continue;
                }
                std::vector<std::string> args = splitStr(line.substr(line.find(' ') + 1, line.size() - line.find(' ')));
                std::string file = args.front();
                args.erase(args.begin());
                ecs::Entities loaded_entities = loadScene(file, args);
                is_components = false;

                for (auto it = loaded_entities.begin(); it != loaded_entities.end(); ++it)
                    entities.push_back(*it);
                continue;
            }

            if (is_components) {
                std::istringstream data = std::istringstream();
                std::string component_name = trimString(line.substr(0, line.find(' ')));

                if (line.find(' ') != std::string::npos)
                    data = std::istringstream(trimString(line.substr(line.find(' '), line.size() - line.find(' '))));

                if (!addComponentPattern(m_world, entity, component_name, data)) {
                    std::cout << "Failed to load scene:" << std::endl;
                    std::cout << "Failed to add component '" << component_name << "' at line " << line_index << " on file " << file_name << " for entity " << entity << std::endl;
                    Application::getInstance().close();
                    return entities;
                }
            } else {
                std::vector<std::string> args = splitStr(line.substr(line.find(' ') + 1, line.size() - line.find(' ')));

                if (args.size() != 1) {
                    std::cout << "Failed to load scene:" << std::endl;
                    std::cout << "Failed to extract system name at line " << line_index << " on file " << file_name << std::endl;
                    return entities;
                }

                std::string system_name = args[0];

                if (!addSystemPattern(m_world, system_name)) {
                    std::cout << "Failed to load scene:" << std::endl;
                    std::cout << "Failed to add system '" << system_name << "' at line " << line_index << " on file " << file_name << " for entity " << entity << std::endl;
                    Application::getInstance().close();
                    return entities;
                }
            }
        }
        return entities;
    }

    void Scene::applyArgs(std::string &scene, const std::vector<std::string> &args)
    {
        std::string key = std::string();
        std::size_t pos = 0;

        for (std::size_t i = 0; i < args.size(); ++i) {
            key = concat("${", i, "}");
            pos = 0;

            while ((pos = scene.find(key, pos)) != std::string::npos)
                scene.replace(pos, key.size(), args.at(i) == "*" ? "" : args.at(i));
        }
    }

    void Scene::calculateArgs(std::string &scene)
    {
        std::size_t pos = 0;
        std::size_t size = 0;

        if ((pos = scene.find("(", pos)) != std::string::npos) {
            size = getArgLength(scene, pos);
            scene.replace(pos, size, calculate(scene.substr(pos, size)));
            calculateArgs(scene);
        }
    }

    std::string Scene::calculate(const std::string &calculus)
    {
        mu::Parser parser;

        try {
            parser.SetExpr(calculus);
            return std::to_string(parser.Eval());

        } catch (mu::Parser::exception_type &e) {
            std::cerr << "Failed to parse: " << calculus << std::endl;
            Application::getInstance().close();
        }
        return std::string();
    }

    std::size_t Scene::getArgLength(const std::string &scene, std::size_t start)
    {
        std::size_t depth = 1;
        std::size_t size = 1;

        for (auto c = scene.begin() + start + 1; c != scene.end() && depth; ++c) {
            depth += *c == '(' ? 1 : *c == ')' ? -1 : 0;
            ++size;
        }

        if (depth) {
            std::cerr << "Failed to parse scene. '(' was never closed" << std::endl;
            Application::getInstance().close();
        }

        return size;
    }

    std::string Scene::trimString(const std::string& str)
    {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");

        if (start == std::string::npos)
            return std::string();

        return str.substr(start, end - start + 1);
    }

    std::vector<std::string> Scene::splitStr(const std::string &str)
    {
        std::vector<std::string> result;
        std::istringstream iss(str);
        std::string token = std::string();
        std::size_t pos = 0;

        while (std::getline(iss, token, ' ')) {
            pos = 0;
            while ((pos = token.find_first_of("\r\n\t", pos)) != std::string::npos)
                token[pos] = ' ';

            if (!token.empty())
                result.push_back(token);
        }

        return result;
    }
}
