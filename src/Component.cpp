#include "Component.hpp"

sdlbox::Component::~Component() {
    for (auto l : eventListeners) {
        delete l.second;
    }
}

int sdlbox::Component::getX() const {
    return x;
}

int sdlbox::Component::getY() const {
    return y;
}

sdlbox::Component* sdlbox::Component::withPosition(int x, int y) {
    this->x = x;
    this->y = y;
    return this;
}

sdlbox::Component* sdlbox::Component::withPosition(Component* relative, int x, int y) {
    this->x = relative->getX() + x;
    this->y = relative->getY() + y;
    return this;
}

int sdlbox::Component::getVerticalPadding() const {
    return vPad;
}

int sdlbox::Component::getHorizontalPadding() const {
    return hPad;
}

sdlbox::Component* sdlbox::Component::withVPad(int amount) {
    vPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withHPad(int amount) {
    hPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withPadding(int vPad, int hPad) {
    this->vPad = vPad;
    this->hPad = hPad;
    return this;
}

void sdlbox::Component::handle(const SDL_Event &e) {
    auto l = eventListeners.find(e.type);
    if (l != eventListeners.end())
        (l->second)->handle(e);
}

void sdlbox::Component::addEventListener(int eventType, EventListener* l) {
    eventListeners[eventType] = l;
}

bool sdlbox::Component::receivePosition() const {
    return true;
}
