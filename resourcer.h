#ifndef RESOURCER_H
#define RESOURCER_H

#include <map>

#include <SFML/Graphics.hpp>

namespace BAMF {

class Resourcer {
    public:
        Resourcer();
        ~Resourcer();

        void loadTexture(std::string, std::string);
        sf::Texture& getTexture(std::string);

        void loadFont(std::string, std::string);
        sf::Font& getFont(std::string);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
};

} // namespace BAMF


#endif // RESOURCER_H
