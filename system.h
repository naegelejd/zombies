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
            for (auto& id : interested) {
                if (!e->hasComponent(id)) {
                    return;
                }
            }
            // LOG: std::cout << "adding entity to system" << std::endl;
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

        virtual void update(void);
};

class RotationSystem : public System {
    public:
        RotationSystem()
        {
            interested.insert(VelocityComponentID);
            interested.insert(RenderableComponentID);
        }

        ~RotationSystem() { }

        virtual void update(void);
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

        virtual void update(void);

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

        virtual void update(void);
};

class ButtonSystem : public System {
    public:
        ButtonSystem()
        {
            interested.insert(ReadableComponentID);
            interested.insert(InputComponentID);
        }

        ~ButtonSystem() { }

        virtual void update(void);
};

class FlockSystem : public System {
public:
    FlockSystem()
    {
        interested.insert(VelocityComponentID);
        interested.insert(FlockMemberComponentID);
    }

    ~FlockSystem() {}

    virtual void update(void);
};

} // namespace BAMF

#endif // SYSTEM_H
