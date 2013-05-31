#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "State.h"

namespace BAMF {

class PlayState : public State {
    public:
        PlayState();
        ~PlayState();
        virtual void update(void);
        virtual void render(sf::RenderWindow&);
        virtual void add(Actor*);
};

} // namespace BAMF

#endif // PLAY_STATE_H
