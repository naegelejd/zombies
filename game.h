#ifndef GAME_H
#define GAME_H

#include <stack>

#include "state.h"

namespace BAMF {

class Game {
    public:
        Game(unsigned int, unsigned int, const std::string&);
        Game(const std::string&);
        ~Game();
        void run(void);
        State& currentState(void);
        void pushState(State*);
        State& popState(void);
    private:
        sf::RenderWindow window;
        std::stack<State*> states;
};

} // namespace BAMF

#endif // GAME_H
