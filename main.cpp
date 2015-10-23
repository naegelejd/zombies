#include "configurator.h"
#include "resourcer.h"
#include "game.h"
#include "entity.h"
#include "state.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <iostream>
#include <vector>

#include <random>

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

    sf::IntRect rect(0, 0, 32, 32);
    sf::Vector2f orig(rect.left + (rect.width / 2),
            rect.top + (rect.height / 2));

    sf::Sprite player_sprite;
    player_sprite.setTexture(resourcer.getTexture("player"));
    player_sprite.setTextureRect(rect);
    player_sprite.setOrigin(orig);

    sf::Sprite zombie_sprite;
    zombie_sprite.setTexture(resourcer.getTexture("zombie"));
    zombie_sprite.setTextureRect(rect);
    zombie_sprite.setOrigin(orig);


    BAMF::Game& game = BAMF::Game::getInstance();
    unsigned int width = 512, height = 384;
    game.init(width, height, configurator.getString("title"));

    BAMF::InputSystem is;
    BAMF::MovementSystem ms;
    BAMF::RotationSystem rots;
    BAMF::RenderSystem rs(game.getWindow());
    BAMF::FlockSystem fs;
    BAMF::State playstate;
    playstate.addSystem(&is);
    playstate.addSystem(&ms);
    playstate.addSystem(&rots);
    playstate.addSystem(&rs);
    playstate.addSystem(&fs);

    BAMF::Entity player;
    auto p = std::make_shared<BAMF::PositionComponent>();
    auto v = std::make_shared<BAMF::VelocityComponent>();
    auto r = std::make_shared<BAMF::RenderableComponent>(player_sprite);
    auto i = std::make_shared<BAMF::InputComponent>();
    player.addComponent(p);
    player.addComponent(v);
    player.addComponent(r);
    player.addComponent(i);
    playstate.addEntity(&player);

    std::vector<BAMF::Entity> zombies(5);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_x(0, width);
    std::uniform_int_distribution<> random_y(0, height);
    for (auto& z: zombies) {
        auto p = std::make_shared<BAMF::PositionComponent>(random_x(gen), random_y(gen));
        auto v = std::make_shared<BAMF::VelocityComponent>();
        auto f = std::make_shared<BAMF::FlockMemberComponent>();
        auto r = std::make_shared<BAMF::RenderableComponent>(zombie_sprite);
        z.addComponent(p);
        z.addComponent(v);
        z.addComponent(f);
        z.addComponent(r);
        std::cout << &z << std::endl;
        playstate.addEntity(&z);
    }

    game.pushState(&playstate);

    sf::Text load_text("Press ENTER to Play!", resourcer.getFont("deja"));
    load_text.setCharacterSize(24);
    load_text.setColor(sf::Color::White);
    // center the text
    load_text.setOrigin(load_text.getLocalBounds().width / 2, load_text.getLocalBounds().height / 2);
    load_text.setPosition(width/2, height/2);
    sf::RenderTexture load_texture;
    if (!load_texture.create(width, height)) {
        std::cerr << "crap" << std::endl;
        exit(EXIT_FAILURE);
    }
    load_texture.clear(sf::Color::Black);
    load_texture.draw(load_text);
    load_texture.display();

    sf::Sprite load_sprite(load_texture.getTexture());

    BAMF::Entity load_screen;
    auto lpc = std::make_shared<BAMF::PositionComponent>();
    auto lrc = std::make_shared<BAMF::RenderableComponent>(load_sprite);
    load_screen.addComponent(lpc);
    load_screen.addComponent(lrc);

    BAMF::RenderSystem lrs(game.getWindow());
    BAMF::ButtonSystem bs;
    BAMF::State loadstate;
    loadstate.addSystem(&lrs);
    loadstate.addSystem(&bs);
    loadstate.addEntity(&load_screen);

    game.pushState(&loadstate);

    game.run();

    return EXIT_SUCCESS;
}
