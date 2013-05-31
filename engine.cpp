#include <iostream>

#include "engine.h"

namespace BAMF {

Engine::Engine()
    : resources_loaded(false)
{ }

void Engine::start(unsigned int resX, unsigned int resY, const std::string& title)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::VideoMode videoMode(resX, resY, desktop.bitsPerPixel);
    window.create(videoMode, title);
}

void Engine::start(const std::string& title)
{
    /*
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    if (modes.size() == 0) {
        std::cout << "No valid fullscreen modes available" << std::endl;
    }
    window.create(modes[0], title);
    */
    window.create(sf::VideoMode::getDesktopMode(), title);
}

void Engine::run()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        inputter.doCallbacks();

        std::vector<Actor*>::iterator actor;

        for (actor = actors.begin(); actor != actors.end(); ++actor) {
            (*actor)->update();
        }

        window.clear();

        for (actor = actors.begin(); actor != actors.end(); ++actor) {
            (*actor)->render(window);
        }

        window.display();
    }
}

Inputter& Engine::getInputter(void)
{
    return inputter;
}

void Engine::addActor(Actor* actor)
{
    actors.push_back(actor);
}

Engine::~Engine() { }

} // namespace BAMF
