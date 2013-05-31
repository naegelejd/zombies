#ifndef FLOCK_H
#define FLOCK_H

#include <SFML/Graphics.hpp>

#include "Zombie.h"

class Flock : public BAMF::Actor {
    public:
        Flock();
        ~Flock();

        void update(void);
        void render(sf::RenderWindow&);

        void add(Zombie&);
        void setFollowee(BAMF::Actor*);

    private:
        const sf::Vector2f guide(Zombie&);
        const sf::Vector2f rule1(Zombie&);
        const sf::Vector2f rule2(Zombie&);
        const sf::Vector2f rule3(Zombie&);

        std::vector<Zombie> m_flock;
        BAMF::Actor* followee;
};

#endif // FLOCK_H
