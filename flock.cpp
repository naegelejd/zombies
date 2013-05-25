#include <cmath>
#include <iostream>

#include "flock.h"

Flock::Flock()
    : BAMF::Actor()
{}

Flock::~Flock() {}

void Flock::update(void)
{
    std::vector<Zombie>::iterator iter;
    for (iter = m_flock.begin(); iter != m_flock.end(); ++iter)
    {
        sf::Vector2f vel = guide(*iter) + rule1(*iter) + rule2(*iter) + rule3(*iter);
        iter->setVelocity(vel);
        iter->update();
    }
}

void Flock::render(sf::RenderWindow& target)
{
    std::vector<Zombie>::iterator iter;
    for (iter = m_flock.begin(); iter != m_flock.end(); ++iter)
    {
        target.draw(*iter);
    }
}

void Flock::setFollowee(BAMF::Actor* f)
{
    followee = f;
}

void Flock::add(Zombie& entity)
{
    m_flock.push_back(entity);
}

const sf::Vector2f Flock::guide(Zombie& zom)
{
    return (followee->getPosition() - zom.getPosition()) / (float)1000;
}

const sf::Vector2f Flock::rule1(Zombie& zom)
{
    sf::Vector2f result;

    std::vector<Zombie>::iterator iter;
    for (iter = m_flock.begin(); iter != m_flock.end(); ++iter) {
        if (zom != *iter) {
            result += iter->getPosition();
        }
    }

    result = result / (float)(m_flock.size() - 1);
    result = (result - zom.getPosition()) / (float)10;

    return result;
}

const sf::Vector2f Flock::rule2(Zombie& zom)
{
    sf::Vector2f result;

    std::vector<Zombie>::iterator iter;
    for (iter = m_flock.begin(); iter != m_flock.end(); ++iter) {
        if (zom != *iter) {
            sf::Vector2f diff = zom.getPosition() - iter->getPosition();
            float length = sqrt(diff.x * diff.x + diff.y * diff.y);

            if (length < zom.getTextureRect().width) {
                result = result - (diff / (float)10);
            }
        }
    }
    return result;
}

const sf::Vector2f Flock::rule3(Zombie& zom)
{
    sf::Vector2f result;

    std::vector<Zombie>::iterator iter;
    for (iter = m_flock.begin(); iter != m_flock.end(); ++iter) {
        if (zom != *iter) {
            result += zom.getVelocity();
        }
    }
    result = result / float(m_flock.size() - 1);
    result = (result - zom.getVelocity()) * (float)10;// / float(8.0);

    return result;
}
