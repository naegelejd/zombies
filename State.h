#ifndef STATE_H
#define STATE_H

#include "Actor.h"

namespace BAMF {

class State {
    public:
        State() { };
        virtual ~State() { };
        virtual void update(void) = 0;
        virtual void render(sf::RenderWindow&) = 0;
        virtual void add(Actor*) = 0;
    private:
        State(const State&);
        State& operator=(const State&);
    protected:
        std::vector<Actor*> actors;
};

} // namespace BAMF

#endif // STATE_H
