#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "configurator.h"
#include "resourcer.h"
#include "game.h"
#include "entity.h"
#include "state.h"


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

    std::map<std::string, std::string> sounds;
    try {
       sounds = configurator.getTable("sounds");
    } catch (const std::exception& err) {
        std::cerr << "Failed to find sounds table" << std::endl;
        exit(EXIT_FAILURE);
    }

    resourcer.loadFonts(fonts);
    resourcer.loadTextures(textures);
    resourcer.loadSounds(sounds);

    sf::Sprite player_sprite;
    player_sprite.setTexture(resourcer.getTexture("player"));
    sf::IntRect rect(0, 0, 32, 32);
    player_sprite.setTextureRect(rect);
    sf::Vector2f orig(rect.left + (rect.width / 2),
            rect.top + (rect.height / 2));
    player_sprite.setOrigin(orig);

    BAMF::Game &game = BAMF::Game::getInstance();
    game.init(512, 384, configurator.getString("title"));

    BAMF::Entity player;
    BAMF::PositionComponent p;
    BAMF::VelocityComponent v;
    BAMF::RenderableComponent r(player_sprite);
    BAMF::InputComponent i;
    player.addComponent(&p);
    player.addComponent(&v);
    player.addComponent(&r);
    player.addComponent(&i);

    BAMF::InputSystem is;
    BAMF::MovementSystem ms;
    BAMF::RotationSystem rots;
    BAMF::RenderSystem rs(game.getWindow());
    BAMF::State playstate;
    playstate.addSystem(&is);
    playstate.addSystem(&ms);
    playstate.addSystem(&rots);
    playstate.addSystem(&rs);

    playstate.addEntity(&player);

    game.pushState(&playstate);

    sf::Text load_text("Play!", resourcer.getFont("deja"));
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

    sf::Sprite load_sprite(load_texture.getTexture());

    BAMF::Entity load_screen;
    BAMF::PositionComponent lpc;
    BAMF::RenderableComponent lrc(load_sprite);
    load_screen.addComponent(&lpc);
    load_screen.addComponent(&lrc);

    BAMF::RenderSystem lrs(game.getWindow());
    BAMF::State loadstate;
    loadstate.addSystem(&lrs);
    loadstate.addEntity(&load_screen);

    game.pushState(&loadstate);

    game.run();

    return EXIT_SUCCESS;
}
