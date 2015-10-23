#include "system.h"
#include "game.h"

#include <random>


namespace BAMF {

void MovementSystem::update(void)
{
    for (auto& e : entities) {
        PositionComponent* p = static_cast<PositionComponent*>(
                e->getComponent(PositionComponentID).get());
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID).get());
        p->x += v->x;
        p->y += v->y;
    }
}

void RotationSystem::update(void)
{
    for (auto&e : entities) {
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID).get());
        RenderableComponent* r = static_cast<RenderableComponent*>(
                e->getComponent(RenderableComponentID).get());

        if (!(v->y == 0 && v->x == 0)) {
            float angle = atan2(v->y, v->x) * 180 / M_PI;
            r->sprite.setRotation(angle);
        }
    }
}

void RenderSystem::update(void)
{
    window.clear();
    for (auto&e : entities) {
        PositionComponent* p = static_cast<PositionComponent*>(
                e->getComponent(PositionComponentID).get());
        RenderableComponent* r = static_cast<RenderableComponent*>(
                e->getComponent(RenderableComponentID).get());
        r->sprite.setPosition(p->x, p->y);
        //std::cout << p->x << ", " << p->y << std::endl;
        window.draw(r->sprite);
    }
    window.display();
}

void InputSystem::update(void)
{
    for (auto& e : entities) {
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID).get());

        int x = 0, y = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            x = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            x = -1;
        else
            x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            y = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            y = -1;
        else
            y = 0;

        if (x && y) {
            float diag = sqrt(2.0) / 2.0;
            v->x = x * diag;
            v->y = y * diag;
        } else {
            v->x = x;
            v->y = y;
        }
    }
}

void ButtonSystem::update(void)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        Game& game = Game::getInstance();
        game.popState();
    }
}


void FlockSystem::update(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-2, 2);

    for (auto& e: entities) {
        FlockMemberComponent* f = static_cast<FlockMemberComponent*>(
                e->getComponent(FlockMemberComponentID).get());
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID).get());

        int x = dis(gen);
        int y = dis(gen);

        if (x && y) {
            float diag = sqrt(2.0) / 2.0;
            v->x = x * diag;
            v->y = y * diag;
        } else {
            v->x = x;
            v->y = y;
        }
    }
}

} // namespace BAMF
