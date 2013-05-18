#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

static int test(lua_State *L)
{
    printf("this is a test\n");
    return 0;
}

void loop(const char *message)
{
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Missing config filename\n");
        return EXIT_FAILURE;
    }

    lua_State *L = luaL_newstate();
    if (L == NULL) {
        fprintf(stderr, "Failed to create Lua state\n");
        return EXIT_FAILURE;
    }

    luaL_openlibs(L);

    lua_pushcfunction(L, test);
    lua_setglobal(L, "test");

    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "Failed to load/run file\n");
        return EXIT_FAILURE;
    }

    lua_getglobal(L, "msg");
    const char *msg = lua_tostring(L, -1);

    sf::RenderWindow window(sf::VideoMode(512, 256), "SFML Text Input System");

    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Menlo.ttc")) {
        std::cerr << "Error loading Menlo.ttc" << std::endl;
        exit(EXIT_FAILURE);
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    std::string str(msg);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    str += static_cast<char>(event.text.unicode);
                }
            }

            text.setString(str);
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }

    lua_close(L);

    return EXIT_SUCCESS;
}
