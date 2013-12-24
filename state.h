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
            std::vector<System*>::iterator sys_iter;
            for (sys_iter = systems.begin(); sys_iter != systems.end(); ++sys_iter) {
                // try to add to every system
                (*sys_iter)->update();
            }
        }

        virtual void addEntity(Entity* entity)
        {
            std::vector<System*>::iterator sys_iter;
            for (   sys_iter = systems.begin();
                    sys_iter != systems.end();
                    ++sys_iter) {
                // try to add to every system
                (*sys_iter)->addEntity(entity);
            }
        }

        virtual void addSystem(System* system)
        {
            systems.push_back(system);
        }

    private:
        State(const State&);
        State& operator=(const State&);
    protected:
        std::vector<System*> systems;
};

} // namespace BAMF

#endif // STATE_H
