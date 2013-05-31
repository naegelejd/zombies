#include "button.h"

namespace BAMF {

Button::Button()
    : hasFocus(false)
{ }

void Button::update(void)
{
}

void Button::render(sf::RenderWindow& win)
{
    win.draw(*this);
}

void Button::toggleFocus(void)
{
    hasFocus = !hasFocus;
}

Button::~Button() {}

} // namespace BAMF
