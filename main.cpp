#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "engine.h"
#include "configurator.h"
#include "player.h"
#include "zombie.h"
#include "flock.h"


static int test(lua_State *L)
{
    printf("this is a test\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Missing config filename\n");
        return EXIT_FAILURE;
    }

    BAMF::Engine engine;

    BAMF::Configurator& configurator = engine.getConfigurator();
    //configurator.registerFunction("test", test);

    engine.config(argv[1]);

    engine.start(512, 384, "My Game!");

    sf::Thread thread(&BAMF::Engine::load, &engine);
    //engine.load();
    thread.launch();
    thread.wait();

    BAMF::Resourcer& resourcer = engine.getResourcer();

    sf::Text text("Loading...", resourcer.getFont("menlo"));
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Texture pt = resourcer.getTexture("player");
    Player player;
    player.setTexture(resourcer.getTexture("player"));
    player.setTextureRect(sf::IntRect(0, 0, 32, 32));

    engine.addActor(&player);

    Flock flock;
    for (int i = 0; i < 10; i++) {
        Zombie zombie;
        zombie.setTexture(resourcer.getTexture("zombie"));
        zombie.setTextureRect(sf::IntRect(0, 0, 32, 32));
        flock.add(zombie);
    }

    flock.setFollowee(&player);

    engine.addActor(&flock);

    engine.run();

    return EXIT_SUCCESS;
}
