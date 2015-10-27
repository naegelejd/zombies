#ifndef STATE_H
#define STATE_H

#include "entity.h"
#include "system.h"

namespace BAMF {

class State {
    public:
        State() { };
        virtual ~State() { };

        virtual void update(void)
        {
            for (auto& sys: systems) {
                sys->update();
            }
        }

        virtual void addEntity(const std::shared_ptr<Entity>& entity)
        {
            for (auto& sys: systems) {
                sys->addEntity(entity);
            }
        }

        virtual void addSystem(const std::shared_ptr<System>& system)
        {
            systems.push_back(system);
        }

    protected:
        std::vector<std::shared_ptr<System> > systems;
};

} // namespace BAMF

#endif // STATE_H
