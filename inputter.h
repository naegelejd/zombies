#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <iostream>

#include <SFML/Window.hpp>

namespace BAMF {

typedef void (*InputCallback)(void);

class Inputter {
    public:
        Inputter();
        ~Inputter();

        void addCallback(sf::Keyboard::Key, InputCallback);
        void doCallbacks(void);

    private:
        //InputCallback[sf::Keyboard::KeyCount] callbacks;
        std::map<sf::Keyboard::Key, InputCallback> callbacks;
};

} // namespace BAMF

#endif // INPUT_H
