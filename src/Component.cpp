#include "Component.hpp"
#include <iostream> // testing

std::mutex sdlbox::mtx;

sdlbox::Component::~Component() {
    for (auto l : eventListeners) {
        clearEventListeners(l.first);
    }
}

int sdlbox::Component::getX() const {
    return x;
}

int sdlbox::Component::getY() const {
    return y;
}

SDL_Rect sdlbox::Component::getRect() const {
    SDL_Rect r;
    r.x = getX();
    r.y = getY();
    r.w = getWidth();
    r.h = getHeight();

    return r;
}

bool sdlbox::Component::collides(Component* other) const {
    SDL_Rect r1 = getRect();
    SDL_Rect r2 = other->getRect();
    SDL_Rect res;
    return SDL_IntersectRect(&r1, &r2, &res);
}

sdlbox::Component* sdlbox::Component::withPosition(int x, int y, int anchor) {
    if (anchor < -1);
    else if (anchor > 1)
        x -= getWidth();
    else
        x -= getWidth()/2;
    
    if ((anchor + 2) % 3 == 0);
    else if ((anchor - 2) % 3 == 0)
        y -= getHeight();
    else
        y -= getHeight()/2;
    
    this->x = x;
    this->y = y;
    return this;
}

sdlbox::Component* sdlbox::Component::withPosition(Component* relative, int x, int y, int anchor) {
    return withPosition(relative->getX() + x, relative->getY() + y, anchor);
}


sdlbox::Component* sdlbox::Component::withReceivePosition(bool val) {
    this->rcvPos = val;
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
        for (auto evl : l->second) {
            evl->handle(e);
        }
}

void sdlbox::Component::step() { }

void sdlbox::Component::addEventListener(int eventType, EventListener* l) {
    eventListeners[eventType].push_back(l);
}

void sdlbox::Component::clearEventListeners(int eventType) {
    for (auto evl : eventListeners[eventType]) {
        delete evl;
    }
    eventListeners[eventType].clear();
}

bool sdlbox::Component::receivePosition() const {
    return rcvPos;
}
