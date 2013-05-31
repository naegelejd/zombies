#include <cmath>

#include "Player.h"

Player::Player()
    : BAMF::Actor()
{
}

Player::~Player()
{
}

void Player::update(void)
{
    int x = 0, y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        y = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        y = -1;

    if (x || y) {
        if (x && y) {
            float diag = sqrt(2.0) / 2.0;
            setVelocity(sf::Vector2f(x * diag, y * diag));
        } else {
            setVelocity(sf::Vector2f(x, y));
        }

        float angle = atan2(velocity.y, velocity.x) * 180 / M_PI;
        this->setRotation(angle);
        this->move(velocity);
    }
}
