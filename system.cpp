#include "system.h"
#include "game.h"


namespace BAMF {

void MovementSystem::update(void)
{
    for (auto& e : entities) {
        auto p = e->getComponent<PositionComponent>();
        auto v = e->getComponent<VelocityComponent>();
        p->x += v->dx;
        p->y += v->dy;
    }
}

bool MovementSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Position) &&
            e->hasComponent(ComponentID::Velocity)) {
        return true;
    }
    return false;
}

void RotationSystem::update(void)
{
    for (auto&e : entities) {
        auto v = e->getComponent<VelocityComponent>();
        auto r = e->getComponent<RenderableComponent>();

        if (!(v->dy == 0 && v->dx == 0)) {
            float angle = atan2(v->dy, v->dx) * 180 / M_PI;
            r->sprite.setRotation(angle);
        }
    }
}

bool RotationSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Velocity) &&
            e->hasComponent(ComponentID::Renderable)) {
        return true;
    }
    return false;
}

void RenderSystem::update(void)
{
    window.clear();
    for (auto&e : entities) {
        auto p = e->getComponent<PositionComponent>();
        auto r = e->getComponent<RenderableComponent>();
        r->sprite.setPosition(p->x, p->y);
        //std::cout << p->x << ", " << p->y << std::endl;
        window.draw(r->sprite);
    }
    window.display();
}

bool RenderSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Position) &&
            e->hasComponent(ComponentID::Renderable)) {
        return true;
    }
    return false;
}

void InputSystem::update(void)
{
    for (auto& e : entities) {
        auto v = e->getComponent<VelocityComponent>();

        int dx = 0, dy = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dx = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dx = -1;
        else
            dx = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dy = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dy = -1;
        else
            dy = 0;

        if (dx && dy) {
            float diag = sqrt(2.0) / 2.0;
            v->dx = dx * diag;
            v->dy = dy * diag;
        } else {
            v->dx = dx;
            v->dy = dy;
        }
    }
}

bool InputSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Velocity) &&
            e->hasComponent(ComponentID::Input)) {
        return true;
    }
    return false;
}

void ButtonSystem::update(void)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        Game& game = Game::getInstance();
        game.popState();
    }
}

bool ButtonSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Readable) &&
            e->hasComponent(ComponentID::Input)) {
        return true;
    }
    return false;
}

void FlockSystem::update(void)
{
    for (auto& entity: entities) {
        auto f = entity->getComponent<FlockMemberComponent>();
        auto vel = entity->getComponent<VelocityComponent>();
        auto pos = entity->getComponent<PositionComponent>();

        // TODO: this should come from elsewhere :(
        double radius = 16;

        // TODO: rule 0: flock should follow player (messages?)

        // rule 1: flock toward the average position of all others
        double dx1 = 0, dy1 = 0;
        for (auto& e: entities) {
            if (e != entity) {
                auto p = e->getComponent<PositionComponent>();
                /* calculate vector *from* pos(x,y) *to* p(x,y) */
                dx1 += p->x - pos->x;
                dy1 += p->y - pos->y;
            }
        }
        dx1 /= entities.size() - 1;
        dy1 /= entities.size() - 1;
        dx1 /= 100;
        dy1 /= 100;

        // rule 2: flock away from the average position of all others
        double dx2 = 0, dy2 = 0;
        for (auto& e: entities) {
            if (e != entity) {
                auto p = e->getComponent<PositionComponent>();

                double x = pos->x - p->x;
                double y = pos->y - p->y;
                double distance = sqrt(x*x + y*y);

                // TODO: this should be a multiple of the sprite's radius!
                double min_distance = 5 * radius;
                if (distance < min_distance) {
                    dx2 += (pos->x - p->x);
                    dy2 += (pos->y - p->y);
                }
            }
        }
        dx2 /= entities.size() - 1;
        dy2 /= entities.size() - 1;
        dx2 /= 5;
        dy2 /= 5;

        // rule 3: move in the same direction as the others
        double dx3 = 0, dy3 = 0;
        for (auto& e: entities) {
            if (e != entity) {
                auto v = e->getComponent<VelocityComponent>();
                dx3 += v->dx;
                dy3 += v->dy;
            }
        }
        dx3 /= entities.size() - 1;
        dy3 /= entities.size() - 1;
        dx3 /= 8;
        dy3 /= 8;

        // rule 4
        // TODO: bound position?

        double dx = dx1 + dx2 + dx3;
        double dy = dy1 + dy2 + dy3;
        double length = sqrt(dx*dx + dy*dy);
        // TODO: this should be a multiple of the sprite's radius!
        double max_velocity = radius / 2;
        if (length > max_velocity) {
            dx = dx / length * max_velocity;
            dy = dy / length * max_velocity;
        }

        /* if (dx && dy) { */
        /*     float diag = sqrt(2.0) / 2.0; */
        /*     vel->dx = dx * diag; */
        /*     vel->dy = dy * diag; */
        /* } else { */
            vel->dx = dx;
            vel->dy = dy;
        /* } */
    }
}

bool FlockSystem::isInterested(const std::shared_ptr<Entity>& e) {
    if (e->hasComponent(ComponentID::Velocity) &&
            e->hasComponent(ComponentID::FlockMember) &&
            e->hasComponent(ComponentID::Position)) {
        return true;
    }
    return false;
}

} // namespace BAMF
