#include "game.h"

namespace BAMF {

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(unsigned int x, unsigned int y, const std::string& title)
{
    window.create(
            sf::VideoMode(x, y,
                sf::VideoMode::getDesktopMode().bitsPerPixel),
            title);
}

void Game::init(const std::string& title)
{
    window.create(sf::VideoMode::getDesktopMode(), title);
}

void Game::run(void)
{
    if (states.empty()) {
        throw std::runtime_error("Can't run game without any states");
    }

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

        State *state = states.top();
        state->update();
    }
}

State& Game::currentState(void)
{
    return *states.top();
}

void Game::pushState(State* state)
{
    states.push(state);
}

State& Game::popState(void)
{
    State& state = *states.top();
    states.pop();
    return state;
}

sf::RenderWindow& Game::getWindow(void)
{
    return window;
}

} // namespace BAMF
