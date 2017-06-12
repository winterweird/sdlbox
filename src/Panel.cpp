#include "Panel.hpp"
#include "Layout.hpp"
#include <iostream> // testing
#include <algorithm> // std::max

using std::max;

sdlbox::Panel::Panel(int orientation) : orientation(orientation) { }

sdlbox::Panel::~Panel() {
    for (auto c : components) {
        delete c;
    }
}

void sdlbox::Panel::add(Component* c) {
    // TODO: Check how SDLBox handles this, I should probably model Panel at
    // least partly on that
    
    int lPad, rPad, tPad, bPad;
    c->getPadding(lPad, rPad, tPad, bPad);
    
    c->withPosition(this, nextX + lPad, nextY + tPad);
    
    width = max(nextX + c->getWidth() + lPad + rPad, width);
    height = max(nextY + c->getHeight() + tPad + bPad, height);

    if (orientation == Layout::VERTICAL) {
        nextY += c->getHeight() + tPad + bPad;
    }
    else if (orientation == Layout::HORIZONTAL) {
        nextX += c->getWidth() + lPad + rPad;
    }
    
    components.push_back(c);
}

int sdlbox::Panel::getWidth() const {
    return width;
}

int sdlbox::Panel::getHeight() const {
    return height;
}

sdlbox::Component* sdlbox::Panel::withPosition(int x, int y) {
    Component::withPosition(x, y);
    repositionChildren();
    return this;
}

sdlbox::Component* sdlbox::Panel::withPosition(Component* relative, int x, int y) {
    Component::withPosition(relative, x, y);
    repositionChildren();
    return this;
}

void sdlbox::Panel::draw() const {
    for (auto c : components) {
        c->draw();
    }
}

void sdlbox::Panel::handle(const SDL_Event &e) {
    Component::handle(e);
    for (auto c : components) {
        c->handle(e);
    }
}

void sdlbox::Panel::repositionChildren() {
    int nx = 0;
    int ny = 0;
    for (size_t i = 0; i < components.size(); i++) {
        auto c = components[i];

        int lPad, rPad, tPad, bPad;
        c->getPadding(lPad, rPad, tPad, bPad);
        c->withPosition(this, nx + lPad, ny + tPad);
        if (orientation == Layout::VERTICAL) {
            ny += c->getHeight() + tPad + bPad;
        }
        else if (orientation == Layout::HORIZONTAL) {
            nx += c->getWidth() + lPad + rPad;
        }
    }

    nextX = nx;
    nextY = ny;
}
