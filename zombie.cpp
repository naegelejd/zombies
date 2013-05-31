#include <cmath>
#include <iostream>

#include "Zombie.h"

Zombie::Zombie()
    : BAMF::Actor()
{ }

Zombie::~Zombie() { }

void Zombie::update(void)
{
    float angle = atan2(velocity.y, velocity.x) * 180 / M_PI;
    this->setRotation(angle);

    this->move(velocity);
}

bool operator ==(const Zombie& left, const Zombie& right)
{
    return (left.getPosition() == right.getPosition()) &&
            (left.getVelocity() == right.getVelocity());
}

bool operator !=(const Zombie& left, const Zombie& right)
{
    return (left.getPosition() != right.getPosition()) &&
            (left.getVelocity() != right.getVelocity());
}
