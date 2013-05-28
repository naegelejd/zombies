#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "logger.h"
#include "configurator.h"
#include "resourcer.h"
#include "inputter.h"
#include "actor.h"

namespace BAMF {

class Engine {
    public:
        Engine();
        ~Engine();

        void start(unsigned int, unsigned int, const std::string&);
        void start(const std::string&);
        void run();

        void config(const std::string&);

        void load(void);

        Configurator& getConfigurator(void);

        Resourcer& getResourcer(void);

        Inputter& getInputter(void);

        void addActor(Actor* actor);

    private:
        sf::RenderWindow window;
        Logger logger;
        Configurator configurator;
        Resourcer resourcer;
        Inputter inputter;

        std::vector<Actor*> actors;
};


} // namespace BAMF

#endif // ENGINE_H
