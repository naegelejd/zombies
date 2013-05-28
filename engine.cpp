#include <iostream>

#include "engine.h"

namespace BAMF {

Engine::Engine()
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

void Engine::config(const std::string& path)
{
    configurator.readConfig(path);
}

void Engine::load(void)
{
    std::string res;
    try {
        res = configurator.getString("resources");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find resource dir" << std::endl;
        exit(EXIT_FAILURE);
    }
    logger.log("Resource Dir: " + res);
    resourcer.setResourceDir(res);

    std::map<std::string, std::string> fonts;
    try {
        fonts = configurator.getTable("fonts");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find fonts table" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::map<std::string, std::string> textures;
    try {
       textures = configurator.getTable("textures");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find textures table" << std::endl;
        exit(EXIT_FAILURE);
    }

    resourcer.loadFonts(fonts);
    resourcer.loadTextures(textures);

    logger.log("Loaded all resources");
}

Configurator& Engine::getConfigurator(void)
{
    return configurator;
}

Resourcer& Engine::getResourcer(void)
{
    return resourcer;
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
