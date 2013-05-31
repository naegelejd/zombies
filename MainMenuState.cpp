#include <SFML/Graphics.hpp>

#include "MainMenuState.h"

namespace BAMF {

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::update(void)
{
    std::vector<Button*>::iterator iter;
    for (iter = buttons.begin(); iter != buttons.end(); ++iter) {
        (*iter)->update();
    }
}

void MainMenuState::render(sf::RenderWindow& win)
{
    win.draw(background);
    std::vector<Button*>::iterator iter;
    for (iter = buttons.begin(); iter != buttons.end(); ++iter) {
        (*iter)->render(win);
    }
}

void MainMenuState::add(BAMF::Actor* actor)
{
    actors.push_back(actor);
}

} // namespace BAMF
