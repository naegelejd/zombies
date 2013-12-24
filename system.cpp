#include "system.h"
#include "game.h"

namespace BAMF {

void MovementSystem::update(void)
{
    std::vector<Entity*>::iterator e_it;
    for (e_it = entities.begin(); e_it != entities.end(); ++e_it) {
        Entity* e = *e_it;
        PositionComponent* p = static_cast<PositionComponent*>(
                e->getComponent(PositionComponentID));
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID));
        p->x += v->x;
        p->y += v->y;
    }
}

void RotationSystem::update(void)
{
    std::vector<Entity*>::iterator e_it;
    for (e_it = entities.begin(); e_it != entities.end(); ++e_it) {
        Entity* e = *e_it;
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID));
        RenderableComponent* r = static_cast<RenderableComponent*>(
                e->getComponent(RenderableComponentID));

        float angle = atan2(v->y, v->x) * 180 / M_PI;
        r->sprite.setRotation(angle);
    }
}

void RenderSystem::update(void)
{
    window.clear();
    std::vector<Entity*>::iterator e_it;
    for (e_it = entities.begin(); e_it != entities.end(); ++e_it) {
        Entity* e = *e_it;
        PositionComponent* p = static_cast<PositionComponent*>(
                e->getComponent(PositionComponentID));
        RenderableComponent* r = static_cast<RenderableComponent*>(
                e->getComponent(RenderableComponentID));
        r->sprite.setPosition(p->x, p->y);
        //std::cout << p->x << ", " << p->y << std::endl;
        window.draw(r->sprite);
    }
    window.display();
}

void InputSystem::update(void)
{
    std::vector<Entity*>::iterator e_it;
    for (e_it = entities.begin(); e_it != entities.end(); ++e_it) {
        Entity* e = *e_it;
        VelocityComponent* v = static_cast<VelocityComponent*>(
                e->getComponent(VelocityComponentID));

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
                v->x = x * diag;
                v->y = y * diag;
            } else {
                v->x = x;
                v->y = y;
            }
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

} // namespace BAMF
