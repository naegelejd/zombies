#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Actor.h"

class Player : public BAMF::Actor
{
    public:
        Player();
        ~Player();

        void update(void);

    private:
        int lives;
};

#endif // PLAYER_H
