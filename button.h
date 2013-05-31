#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

namespace BAMF {

class Button : public sf::Text {
    public:
        Button();
        ~Button();
        void update(void);
        void render(sf::RenderWindow&);

        void toggleFocus(void);
    private:
        bool hasFocus;
};

} // namespace BAMF

#endif // BUTTON_H
