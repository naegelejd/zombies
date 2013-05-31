#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "logger.h"
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

        Inputter& getInputter(void);

        void addActor(Actor* actor);

        sf::Mutex mutex;
        bool resources_loaded;

    private:
        sf::RenderWindow window;
        Logger logger;
        Inputter inputter;

        std::vector<Actor*> actors;
};


} // namespace BAMF

#endif // ENGINE_H
