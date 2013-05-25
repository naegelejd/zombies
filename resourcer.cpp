#include <iostream>

#include "resourcer.h"

namespace BAMF {

Resourcer::Resourcer()
{

}

Resourcer::~Resourcer() { }

void Resourcer::loadTexture(std::string path, std::string name)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture at: " << path << std::endl;
    } else {
        textures[name] = texture;
    }
}

sf::Texture& Resourcer::getTexture(std::string name)
{
    // this may throw an exception
    return textures.at(name);
}

void Resourcer::loadFont(std::string path, std::string name)
{
    sf::Font font;
    if (!font.loadFromFile(path)) {
        std::cerr << "Error loading font from: " << path << std::endl;
    } else {
        fonts[name] = font;
    }
}

sf::Font& Resourcer::getFont(std::string name)
{
    // this may throw an exception
    return fonts.at(name);
}

} // namespace BAMF
