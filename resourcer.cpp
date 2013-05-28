#include <iostream>

#include "resourcer.h"

namespace BAMF {

Resourcer::Resourcer()
{

}

Resourcer::~Resourcer() { }

void Resourcer::setResourceDir(const std::string& res)
{
    resource_directory = res;
}

void Resourcer::loadTextures(const std::map<std::string, std::string>& paths)
{
    textureLoader.loadFromMap(resource_directory, paths);
}

void Resourcer::loadFonts(const std::map<std::string, std::string>& paths)
{
    fontLoader.loadFromMap(resource_directory, paths);
}

const sf::Texture& Resourcer::getTexture(const std::string& name)
{
    try {
        return textureLoader.getResource(name);
    } catch (const std::exception& err) {
        std::cerr << "Failed to get texture " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

const sf::Font& Resourcer::getFont(const std::string& name)
{
    try {
        return fontLoader.getResource(name);
    } catch (const std::exception& err) {
        std::cerr << "Failed to get font " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

} // namespace BAMF
