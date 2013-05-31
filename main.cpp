#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Configurator.h"
#include "Resourcer.h"
#include "Game.h"
#include "LoadState.h"
#include "PlayState.h"
#include "Player.h"
#include "Zombie.h"
#include "Flock.h"


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
    //configurator.registerFunction("test", test);

    configurator.readConfig(argv[1]);

    BAMF::Resourcer resourcer;
    std::string res;
    try {
        res = configurator.getString("resources");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find resource dir" << std::endl;
        exit(EXIT_FAILURE);
    }
    resourcer.setResourceDir(res);

    std::map<std::string, std::string> fonts;
    try {
        fonts = configurator.getTable("fonts");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find fonts table" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::map<std::string, std::string> textures;
    try {
       textures = configurator.getTable("textures");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find textures table" << std::endl;
        exit(EXIT_FAILURE);
    }

    resourcer.loadFonts(fonts);
    resourcer.loadTextures(textures);


    BAMF::Game game(512, 384, configurator.getString("title"));

    BAMF::PlayState playstate;

    Player player;
    player.setTexture(resourcer.getTexture("player"));
    player.setTextureRect(sf::IntRect(0, 0, 32, 32));
    playstate.add(&player);

    Flock flock;
    for (int i = 0; i < 10; i++) {
        Zombie zombie;
        zombie.setTexture(resourcer.getTexture("zombie"));
        zombie.setTextureRect(sf::IntRect(0, 0, 32, 32));
        flock.add(zombie);
    }

    flock.setFollowee(&player);

    playstate.add(&flock);

    game.pushState(&playstate);

    sf::Text load_text("Loading...", resourcer.getFont("deja"));
    load_text.setCharacterSize(24);
    load_text.setColor(sf::Color::White);
    sf::RenderTexture load_texture;
    if (!load_texture.create(500, 500)) {
        std::cerr << "crap" << std::endl;
        exit(EXIT_FAILURE);
    }
    load_texture.clear(sf::Color::Black);
    load_texture.draw(load_text);
    load_texture.display();

    BAMF::Actor load_screen;
    load_screen.setTexture(load_texture.getTexture());

    BAMF::LoadState loadstate;
    loadstate.add(&load_screen);
    game.pushState(&loadstate);

    game.run();

    return EXIT_SUCCESS;
}
