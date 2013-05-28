#ifndef RESOURCER_H
#define RESOURCER_H

#include <map>
#include <stdexcept>

#include <SFML/Graphics.hpp>

namespace BAMF {

template <class T> class ResLoader
{
public:
    ResLoader() { }
    ~ResLoader() { }

    void loadFromMap(const std::string& resdir, const std::map<std::string, std::string>& paths)
    {
        std::map<std::string, std::string>::const_iterator iter;
        for (iter = paths.begin(); iter != paths.end(); ++iter) {
            T resource;
            std::string path;

            if (iter->second[0] != '/') {
                path += resdir;
            }
            path += iter->second;

            if (!resource.loadFromFile(path)) {
                std::cerr << "Error loading resource from " << path << std::endl;
            } else {
                loaded[iter->first] = resource;
            }
        }
    }

    const T& getResource(const std::string& name)
    {
        return loaded.at(name);
    }

private:
    std::map<std::string, T> loaded;
};


class Resourcer {
    public:
        Resourcer();
        ~Resourcer();

        void setResourceDir(const std::string&);

        void loadFonts(const std::map<std::string, std::string>&);
        void loadTextures(const std::map<std::string, std::string>&);

        const sf::Texture& getTexture(const std::string&);
        const sf::Font& getFont(const std::string&);

    private:
        Resourcer(const Resourcer&);
        Resourcer& operator=(const Resourcer&);

        std::string resource_directory;
        ResLoader<sf::Texture> textureLoader;
        ResLoader<sf::Font> fontLoader;
};

} // namespace BAMF


#endif // RESOURCER_H
