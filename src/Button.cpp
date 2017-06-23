#include "Button.hpp"
#include "GraphicsHelper.hpp"
#include "EventListener.hpp"
#include <iostream> // testing

sdlbox::Button::Button(std::string text, std::function<void (const SDL_Event&)> callback) : Label(text) {
    addEventListener(SDL_MOUSEBUTTONDOWN, new EventListener([this](const SDL_Event& e) {
        return e.button.button == SDL_BUTTON_LEFT
            && e.button.x > getX() && e.button.x < getX() + getWidth()
            && e.button.y > getY() && e.button.y < getY() + getHeight();
    }, callback));
}

sdlbox::Button::Button(std::string text, std::function<bool (const SDL_Event&)> match,
        std::function<void (const SDL_Event&)> callback) : Label(text) {
    addEventListener(SDL_MOUSEBUTTONDOWN, new EventListener(match, callback));
}


int sdlbox::Button::getWidth() const {
    return Label::getWidth() + Label::getHeight()/2;
}

int sdlbox::Button::getHeight() const {
    return Label::getHeight() + Label::getHeight()/2;
}

void sdlbox::Button::draw() const {
    SDL_Rect r;
    r.x = getX();
    r.y = getY();
    r.w = getWidth();
    r.h = getHeight();

    GraphicsHelper::drawRoundedRect(&r, r.h/4, Color(0,0,0));
    Label::draw();
}

sdlbox::Component* sdlbox::Button::withPosition(int x, int y, int anchor) {
    Label::withPosition(x, y, anchor);
    repositionTexture(Label::getHeight()/4, Label::getHeight()/4);
    return this;
}

sdlbox::Component* sdlbox::Button::withPosition(Component* relative, int x, int y, int anchor) {
    Label::withPosition(relative, x, y, anchor);
    repositionTexture(Label::getHeight()/4, Label::getHeight()/4);
    return this;
}
