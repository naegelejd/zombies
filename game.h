#ifndef GAME_H
#define GAME_H

#include <stdexcept>
#include <stack>

#include "state.h"

namespace BAMF {

class Game {
    public:
        static Game& getInstance()
        {
            static Game instance;
            return instance;
        }

        void init(unsigned int, unsigned int, const std::string&);
        void init(const std::string&);
        void run(void);
        State& currentState(void);
        void pushState(State*);
        State& popState(void);
        sf::RenderWindow& getWindow(void);
    private:
        Game() {};
        ~Game() {};
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        sf::RenderWindow window;
        std::stack<State*> states;
};

} // namespace BAMF

#endif // GAME_H
