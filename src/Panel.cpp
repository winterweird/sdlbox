#include "Panel.hpp"
#include "Layout.hpp"
#include <iostream> // testing
#include <algorithm> // std::max

using std::max;

sdlbox::Panel::Panel(int orientation) : orientation(orientation) {}

sdlbox::Panel::~Panel() {
    for (auto c : components) {
        delete c;
    }
}

void sdlbox::Panel::add(Component* c) {
    // TODO: Check how SDLBox handles this, I should probably model Panel at
    // least partly on that
    components.push_back(c);

    int vPad = c->getVerticalPadding();
    int hPad = c->getHorizontalPadding();

    c->withPosition(this, nextX + hPad, nextY + vPad);
    
    width = max(nextX + c->getWidth() + 2*hPad, width);
    height = max(nextY + c->getHeight() + 2*vPad, height);

    if (orientation == Layout::VERTICAL) {
        nextY += c->getHeight() + 2*vPad;
    }
    else if (orientation == Layout::HORIZONTAL) {
        nextX += c->getWidth() + 2*hPad;
    }
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
    for (auto c : components) {
        c->handle(e);
    }
}

void sdlbox::Panel::repositionChildren() {
    int nx = 0;
    int ny = 0;
    for (size_t i = 0; i < components.size(); i++) {
        auto c = components[i];
        int vPad = c->getVerticalPadding();
        int hPad = c->getHorizontalPadding();
        c->withPosition(this, nx + hPad, ny + vPad);
        if (orientation == Layout::VERTICAL) {
            ny += c->getHeight() + 2*vPad;
        }
        else if (orientation == Layout::HORIZONTAL) {
            nx += c->getWidth() + 2*hPad;
        }
    }
}
