#include "game.h"

namespace BAMF {

Game::Game(unsigned int x, unsigned int y, const std::string& title)
    : window(sf::VideoMode (x, y, sf::VideoMode::getDesktopMode().bitsPerPixel), title)
{
}

Game::Game(const std::string& title)
    : window(sf::VideoMode::getDesktopMode(), title)
{
}

Game::~Game()
{
}

void Game::run(void)
{
    if (states.empty()) {
        std::cerr << "Can't run game without an initial state" << std::endl;
        return;
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
        window.clear();
        state->render(window);
        window.display();
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

} // namespace BAMF
