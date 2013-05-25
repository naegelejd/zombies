#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "logger.h"
#include "resourcer.h"
#include "inputter.h"
#include "actor.h"

namespace BAMF {

class Engine {
    public:
        Engine(unsigned int, unsigned int, std::string);
        Engine(std::string);
        ~Engine();
        void run();

        Resourcer& getResourcer(void);

        Inputter& getInputter(void);

        void addActor(Actor* actor);

    private:
        sf::RenderWindow window;
        Logger logger;
        Resourcer resourcer;
        Inputter inputter;

        std::vector<Actor*> actors;
};

} // namespace BAMF

#endif // ENGINE_H
