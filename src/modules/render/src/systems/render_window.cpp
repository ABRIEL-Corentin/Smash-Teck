////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  render_window.cpp
//
////////////////////////

#include "window.hpp"
#include "systems/render_window.hpp"
#include "ecs/world.hpp"
#include "application.hpp"

namespace render
{
    static void handleEvents(sf::RenderWindow &window)
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    engine::Application::getInstance().close();
                    break;
                default:
                    break;
            }
        }
    }

    void renderWindow()
    {
        static sf::Clock clock = sf::Clock();
        render::Window &window = render::Window::getInstance();

        window.delta_time = clock.restart().asSeconds();
        window.window.display();
        window.window.clear(sf::Color::Black);

        handleEvents(window.window);
    }
}
