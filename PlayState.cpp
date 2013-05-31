#include <SFML/Graphics.hpp>

#include "PlayState.h"

namespace BAMF {

PlayState::PlayState()
{
}

PlayState::~PlayState()
{

}

void PlayState::update(void)
{
    std::vector<Actor*>::iterator iter;
    for (iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->update();
    }
}

void PlayState::render(sf::RenderWindow& win)
{
    std::vector<Actor*>::iterator iter;
    for (iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->render(win);
    }
}

void PlayState::add(Actor* actor)
{
    actors.push_back(actor);
}

} // namespace BAMF
