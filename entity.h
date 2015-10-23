#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

namespace BAMF {

typedef enum {
    EmptyComponentID,
    PositionComponentID,
    VelocityComponentID,
    RenderableComponentID,
    ReadableComponentID,
    InputComponentID,
    AudibleComponentID,
    FlockMemberComponentID,
    COMPONENT_COUNT
} ComponentID;

class Component {
    public:
       Component(ComponentID id) : id(id) { }
       virtual ~Component() { }
       ComponentID getID(void) { return id; }
    private:
        ComponentID id;
};

class PositionComponent : public Component {
    public:
        PositionComponent(float x=0, float y=0)
            : Component(PositionComponentID)
            , x(x), y(y) { }

        ~PositionComponent() { }

        float x;
        float y;
};

class VelocityComponent : public Component {
    public:
        VelocityComponent(float x=0, float y=0)
            : Component(VelocityComponentID)
            , x(x), y(y) {}
        ~VelocityComponent() { }

        float x;
        float y;
};

class RenderableComponent : public Component {
    public:
        RenderableComponent(sf::Sprite& sp)
            : Component(RenderableComponentID)
            , sprite(sp) { }

        ~RenderableComponent() { }

        sf::Sprite sprite;
};

class ReadableComponent : public Component {
    public:
        ReadableComponent(sf::Text& tx)
            : Component(ReadableComponentID)
            , text(tx) { }

        ~ReadableComponent() { }

        sf::Text text;
};

class InputComponent : public Component {
    public:
        InputComponent()
            : Component(InputComponentID) { }
        ~InputComponent() { }

};

class AudibleComponent : public Component {
    public:
        AudibleComponent()
            : Component(AudibleComponentID) { }
        ~AudibleComponent() { }

        sf::Sound sound;
};

class FlockMemberComponent: public Component {
public:
    FlockMemberComponent()
      : Component(FlockMemberComponentID) {}
};


class Entity {
    public:
        Entity() : components(COMPONENT_COUNT) { }
        ~Entity() { }

        void addComponent(const std::shared_ptr<Component>& c)
        {
            std::cout << "adding component " << c << "\n";
            if (c) {
                components[c->getID()] = c;
            }
        }

        bool hasComponent(ComponentID id)
        {
            if (components[id] == NULL) {
                return false;
            }
            return true;
        }

        std::shared_ptr<Component> getComponent(ComponentID id)
        {
            return components[id];
        }

    private:
        std::vector<std::shared_ptr<Component> > components;
};

} // namespace BAMF

#endif // ENTITY_H
