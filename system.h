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

    virtual bool isInterested(const std::shared_ptr<Entity>& e) = 0;

    virtual void addEntity(const std::shared_ptr<Entity>& e)
    {
        if (isInterested(e)) {
            // LOG: std::cout << "adding entity to system" << std::endl;
            entities.push_back(e);
        }
    }

protected:
    std::vector<std::shared_ptr<Entity> > entities;
};

class MovementSystem : public System {
public:
    MovementSystem() {}
    ~MovementSystem() {}

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);
};

class RotationSystem : public System {
public:
    RotationSystem() {}
    ~RotationSystem() { }

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);
};

class RenderSystem : public System {
public:
    RenderSystem(sf::RenderWindow& win)
      : window(win)
    { }
    ~RenderSystem() { }

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);

private:
    sf::RenderWindow& window;
};

class InputSystem : public System {
public:
    InputSystem() {}
    ~InputSystem() { }

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);
};

class ButtonSystem : public System {
public:
    ButtonSystem() {}
    ~ButtonSystem() { }

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);
};

class FlockSystem : public System {
public:
    FlockSystem() {}
    ~FlockSystem() {}

    virtual void update(void);
    virtual bool isInterested(const std::shared_ptr<Entity>& e);
};

} // namespace BAMF

#endif // SYSTEM_H
