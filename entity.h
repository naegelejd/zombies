#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace BAMF {

typedef enum {
    EmptyComponentID,
    PositionComponentID,
    VelocityComponentID,
    RenderableComponentID,
    ReadableComponentID,
    InputComponentID,
    AudibleComponentID,
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
        PositionComponent()
            : Component(PositionComponentID)
            , x(0), y(0) { }
        ~PositionComponent() { }

        float x;
        float y;
};

class VelocityComponent : public Component {
    public:
        VelocityComponent()
            : Component(VelocityComponentID)
            , x(0), y(0) { }
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


class Entity {
    public:
        Entity() { }
        ~Entity() { }

        void addComponent(Component *c)
        {
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

        Component* getComponent(ComponentID id)
        {
            return components[id];
        }

    private:
        Component* components[COMPONENT_COUNT];
};

} // namespace BAMF

#endif // ENTITY_H
