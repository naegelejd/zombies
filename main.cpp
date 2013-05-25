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

    BAMF::Configurator configurator;

    lua_register(configurator.L, "test", test);

    if (luaL_dofile(configurator.L, argv[1]) != 0) {
        fprintf(stderr, "Failed to load/run file\n");
        return EXIT_FAILURE;
    }

    lua_getglobal(configurator.L, "title");
    const char *title = lua_tostring(configurator.L, -1);
    if (!title) {
        fprintf(stderr, "Failed to read 'title' from config\n");
        return EXIT_FAILURE;
    }

    lua_getglobal(configurator.L, "res");
    const char *res = lua_tostring(configurator.L, -1);
    if (!res) {
        fprintf(stderr, "Failed to read 'res' from config\n");
        return EXIT_FAILURE;
    }
    std::string resources(res);

    //BAMF::Engine engine(512, 384, "My Game!");
    BAMF::Engine engine("My Game!");
    BAMF::Resourcer resourcer = engine.getResourcer();
    //BAMF::Inputter inputter = engine.getInputter();

    resourcer.loadFont("/System/Library/Fonts/Menlo.ttc", "menlo");

    sf::Text text;
    text.setFont(resourcer.getFont("menlo"));
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    resourcer.loadTexture(resources + "/player.png", "player");

    Player player;
    player.setTexture(resourcer.getTexture("player"));
    player.setTextureRect(sf::IntRect(0, 0, 32, 32));

    engine.addActor(&player);

    resourcer.loadTexture(resources + "/zombie.png", "zombie");

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
