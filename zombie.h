#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SFML/Graphics.hpp>

#include "actor.h"

class Zombie : public BAMF::Actor
{
    public:
        Zombie();
        ~Zombie();
        void update(void);

    private:
        int health;
};

bool operator ==(const Zombie& left, const Zombie& right);
bool operator !=(const Zombie& left, const Zombie& right);


#endif // ZOMBIE_H
