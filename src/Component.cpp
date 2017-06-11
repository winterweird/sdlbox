#include "Component.hpp"

sdlbox::Component::~Component() {}

int sdlbox::Component::getX() const {
    return x;
}

int sdlbox::Component::getY() const {
    return y;
}

void sdlbox::Component::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void sdlbox::Component::setPosition(Component* relative, int x, int y) {
    this->x = relative->getX() + x;
    this->y = relative->getY() + y;
}

bool sdlbox::Component::receivePosition() const {
    return true;
}
