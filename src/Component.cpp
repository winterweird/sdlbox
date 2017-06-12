#include "Component.hpp"

std::mutex sdlbox::mtx;

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
    return getTopPadding() + getBottomPadding(); // fix
}

int sdlbox::Component::getHorizontalPadding() const {
    return getLeftPadding() + getRightPadding();
}

int sdlbox::Component::getLeftPadding() const {
    return lPad;
}

int sdlbox::Component::getRightPadding() const {
    return rPad;
}

int sdlbox::Component::getTopPadding() const {
    return tPad;
}

int sdlbox::Component::getBottomPadding() const {
    return bPad;
}

void sdlbox::Component::getPadding(int &l, int &r, int &t, int &b) const {
    l = lPad; r = rPad; t = tPad; b = bPad;
}

sdlbox::Component* sdlbox::Component::withVPad(int amount) {
    return withTPad(amount)->withBPad(amount);
}

sdlbox::Component* sdlbox::Component::withHPad(int amount) {
    return withLPad(amount)->withRPad(amount);
}

sdlbox::Component* sdlbox::Component::withLPad(int amount) {
    lPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withRPad(int amount) {
    rPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withTPad(int amount) {
    tPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withBPad(int amount) {
    bPad = amount;
    return this;
}

sdlbox::Component* sdlbox::Component::withPadding(int vPad, int hPad) {
    return withVPad(vPad)->withHPad(hPad);
}

sdlbox::Component* sdlbox::Component::withPadding(int lPad, int rPad, int tPad, int bPad) {
    return withLPad(lPad)->withRPad(rPad)->withTPad(tPad)->withBPad(bPad);
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
