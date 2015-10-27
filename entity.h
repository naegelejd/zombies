#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>
#include <iostream>

namespace BAMF {

enum class ComponentID {
    Empty,
    Position,
    Velocity,
    Renderable,
    Readable,
    Input,
    Audible,
    FlockMember
};

/* utility: see http://stackoverflow.com/a/24847480 */
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class Component {
public:
    Component() { }
    virtual ~Component() { }
    template <class C> static ComponentID getID(void);
};

class PositionComponent : public Component {
public:
    PositionComponent(float x=0, float y=0)
      : x(x), y(y) { }

    float x, y;
};

class VelocityComponent : public Component {
public:
    VelocityComponent(float dx=0, float dy=0)
      : dx(dx), dy(dy) {}

    float dx, dy;
};

class RenderableComponent : public Component {
public:
    RenderableComponent(sf::Sprite& sp)
      : sprite(sp) { }

    sf::Sprite sprite;
};

class ReadableComponent : public Component {
public:
    ReadableComponent(sf::Text& tx)
      : text(tx) { }

    sf::Text text;
};

class InputComponent : public Component {
public:
    InputComponent() {}
};

class AudibleComponent : public Component {
public:
    AudibleComponent() {}

    sf::Sound sound;
};

class FlockMemberComponent: public Component {
public:
    FlockMemberComponent() {}
};

class Entity {
public:
    Entity() { }
    ~Entity() { }

    template <class C>
    void addComponent(const std::shared_ptr<C>& c)
    {
        // LOG: std::cout << "adding component " << c << "\n";
        components_[Component::getID<C>()] = c;
    }

    bool hasComponent(ComponentID id) const
    {
        if (components_.count(id) == 0) {
            return false;
        }
        return true;
    }

    template <class C>
    std::shared_ptr<C> getComponent(void)
    {
        return std::static_pointer_cast<C>(components_[Component::getID<C>()]);
    }

private:
    std::unordered_map<ComponentID, std::shared_ptr<Component>, EnumClassHash> components_;
};

} // namespace BAMF

#endif // ENTITY_H
