#ifndef LOAD_STATE_H
#define LOAD_STATE_H

#include "State.h"

namespace BAMF {

class LoadState : public State {
    public:
        LoadState();
        ~LoadState();
        virtual void update(void);
        virtual void render(sf::RenderWindow&);
        virtual void add(Actor*);
};

} // namespace BAMF

#endif // LOAD_STATE_H
