#include "Button.hpp"
#include "GraphicsHelper.hpp"
#include "EventListener.hpp"

sdlbox::Button::Button(std::string text, std::function<void (const SDL_Event&)> callback) {
    Font* font = GraphicsHelper::getDefaultFont();
    texture = font->render(text, Color(0,0,0));
    
    addEventListener(SDL_MOUSEBUTTONDOWN, new EventListener([this](const SDL_Event& e) {
        return e.button.button == SDL_BUTTON_LEFT
            && e.button.x >= getX() && e.button.x <= getX() + getWidth()
            && e.button.y >= getY() && e.button.y <= getY() + getHeight();
    }, callback));
}

sdlbox::Button::~Button() {
    delete texture;
}

int sdlbox::Button::getWidth() const {
    return texture->getWidth() + texture->getHeight()/2;
}

int sdlbox::Button::getHeight() const {
    return texture->getHeight() + texture->getHeight()/2;
}

void sdlbox::Button::draw() const {
    SDL_Rect r;
    r.x = getX();
    r.y = getY();
    r.w = getWidth();
    r.h = getHeight();

    GraphicsHelper::drawRoundedRect(&r, r.h/4, Color(0,0,0));
    texture->draw();
}

sdlbox::Component* sdlbox::Button::withPosition(int x, int y) {
    Component::withPosition(x, y);
    texture->withPosition(this, getHeight()/4, getHeight()/4);
    return this;
}

sdlbox::Component* sdlbox::Button::withPosition(Component* relative, int x, int y) {
    Component::withPosition(relative, x, y);
    texture->withPosition(this, getHeight()/4, getHeight()/4);
    return this;
}
