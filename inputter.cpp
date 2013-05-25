#include "inputter.h"

namespace BAMF {

Inputter::Inputter()
{
}

Inputter::~Inputter()
{
}

void Inputter::addCallback(sf::Keyboard::Key key, InputCallback cb)
{
    if (key < sf::Keyboard::A || key >= sf::Keyboard::KeyCount) {
        std::cerr << "Invalid keyboard key" << std::endl;
    } else {
        callbacks[key] = cb;
    }
}

void Inputter::doCallbacks(void)
{
    std::map<sf::Keyboard::Key, InputCallback>::iterator iter;
    for (iter = callbacks.begin(); iter != callbacks.end(); ++iter) {
        iter->second();
    }
}

} // namespace BAMF
