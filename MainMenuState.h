#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"

namespace BAMF {

class MainMenuState : public State {
    public:
        MainMenuState();
        ~MainMenuState();
        virtual void update(void);
        virtual void render(sf::RenderWindow&);
        virtual void add(Actor*);
    private:
        sf::Sprite background;
        std::vector<Button*> buttons;
};

} // namespace BAMF

#endif // MAIN_MENU_STATE_H
