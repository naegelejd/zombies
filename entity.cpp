#include "entity.h"

namespace BAMF {

template <class C> ComponentID Component::getID() { return ComponentID::Empty; }
template <> ComponentID Component::getID<PositionComponent>() { return ComponentID::Position; }
template <> ComponentID Component::getID<VelocityComponent>() { return ComponentID::Velocity; }
template <> ComponentID Component::getID<RenderableComponent>() { return ComponentID::Renderable; }
template <> ComponentID Component::getID<ReadableComponent>() { return ComponentID::Readable; }
template <> ComponentID Component::getID<InputComponent>() { return ComponentID::Input; }
template <> ComponentID Component::getID<AudibleComponent>() { return ComponentID::Audible; }
template <> ComponentID Component::getID<FlockMemberComponent>() { return ComponentID::FlockMember; }

} // namespace BAMF
