#include <SFML/Graphics.hpp>

#include "LoadState.h"

namespace BAMF {

LoadState::LoadState()
{
}

LoadState::~LoadState()
{

}

void LoadState::update(void)
{
    std::vector<Actor*>::iterator iter;
    for (iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->update();
    }
}

void LoadState::render(sf::RenderWindow& win)
{
    std::vector<Actor*>::iterator iter;
    for (iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->render(win);
    }
}

void LoadState::add(BAMF::Actor* actor)
{
    actors.push_back(actor);
}

} // namespace BAMF
