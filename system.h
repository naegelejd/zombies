#ifndef SYSTEM_H
#define SYSTEM_H

#include <cmath>
#include <set>
#include <iostream>

#include "entity.h"

namespace BAMF {

class System {
    public:
        System() { }
        ~System() { }

        virtual void update(void) = 0;

        virtual void addEntity(Entity *e)
        {
            std::set<ComponentID>::iterator id;
            for (id = interested.begin(); id != interested.end(); ++id) {
                if (!e->hasComponent(*id)) {
                    return;
                }
            }
            std::cout << "adding entity to system" << std::endl;
            entities.push_back(e);
        }

    protected:
        std::set<ComponentID> interested;
        std::vector<Entity*> entities;
};

class MovementSystem : public System {
    public:
        MovementSystem()
        {
            interested.insert(PositionComponentID);
            interested.insert(VelocityComponentID);
        }

        ~MovementSystem() { }

        virtual void update(void)
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
};

class RenderSystem : public System {
    public:
        RenderSystem(sf::RenderWindow& win)
            : window(win)
        {
            interested.insert(PositionComponentID);
            interested.insert(RenderableComponentID);
        }

        ~RenderSystem() { }

        virtual void update(void)
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

    private:
        sf::RenderWindow& window;
};

class InputSystem : public System {
    public:
        InputSystem()
        {
            interested.insert(VelocityComponentID);
            interested.insert(InputComponentID);
        }

        ~InputSystem() { }

        virtual void update(void)
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

                    //float angle = atan2(velocity.y, velocity.x) * 180 / M_PI;
                    //this->setRotation(angle);
                }
            }
        }
};

class ButtonSystem : public System {
    public:
        ButtonSystem()
        {
            interested.insert(ReadableComponentID);
            interested.insert(InputComponentID);
        }

        ~ButtonSystem() { }

        virtual void update(void)
        {
            
        }
};

} // namespace BAMF

#endif // SYSTEM_H
