#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace BAMF {

class Actor : public sf::Sprite {
    public:
        Actor() { }
        virtual ~Actor() { }

        virtual void update(void)
        {
        }

        virtual void render(sf::RenderWindow& win)
        {
            win.draw(*this);
        }

        void setTextureRect(const sf::IntRect& rect)
        {
            sf::Vector2f orig(rect.left + (rect.width / 2),
                    rect.top + (rect.height / 2));
            this->setOrigin(orig);

            sf::Sprite::setTextureRect(rect);
        }

        const sf::Vector2f& getVelocity() const
        {
            return velocity;
        }

        void setVelocity(const sf::Vector2f& vel)
        {
            velocity = vel;
        }


    protected:
        bool visible;
        sf::Vector2f velocity;
};

} // namespace BAMF

#endif // ACTOR_H
