#include "Panel.hpp"
#include "Layout.hpp"
#include "ComponentFactory.hpp"
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
    int lPad, rPad, tPad, bPad;
    c->getPadding(lPad, rPad, tPad, bPad);
    
    ComponentFactory(c).position(this, nextX + lPad, nextY + tPad);

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

void sdlbox::Panel::draw() const {
    for (auto c : components) {
        c->draw();
    }
}

void sdlbox::Panel::commit() {
    scheduleReposition();
//    repositionChildren();
}

void sdlbox::Panel::handle(const SDL_Event &e) {
    Component::handle(e);
    for (auto c : components) {
        c->handle(e);
    }
}

void sdlbox::Panel::step() {
    for (auto c : components) {
        c->step();
    }

    if (repositionScheduled) {
        repositionChildren();
    }
}

void sdlbox::Panel::scheduleReposition() {
    repositionScheduled = true;
}

void sdlbox::Panel::repositionChildren() {
    int nx = 0;
    int ny = 0;
    int w = 1;
    int h = 1;
    
    for (size_t i = 0; i < components.size(); i++) {
        auto c = components[i];

        int lPad, rPad, tPad, bPad;
        c->getPadding(lPad, rPad, tPad, bPad);
        ComponentFactory(c).position(this, nx + lPad, ny + tPad);
        
        if (orientation == Layout::VERTICAL) {
            ny += c->getHeight() + tPad + bPad;
        }
        else if (orientation == Layout::HORIZONTAL) {
            nx += c->getWidth() + lPad + rPad;
        }

        w = max(c->getX() + c->getWidth() + lPad + rPad, w);
        h = max(c->getY() + c->getHeight() + tPad + bPad, h);
    }

    nextX = nx;
    nextY = ny;

    width = w;
    height = h;
}
