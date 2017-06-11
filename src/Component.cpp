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

int sdlbox::Component::getVerticalPadding() const {
    return vPad;
}

int sdlbox::Component::getHorizontalPadding() const {
    return hPad;
}

void sdlbox::Component::setVerticalPadding(int amount) {
    vPad = amount;
}

void sdlbox::Component::setHorizontalPadding(int amount) {
    hPad = amount;
}

void sdlbox::Component::setPadding(int verticalPadding, int horizontalPadding) {
    setVerticalPadding(verticalPadding);
    setHorizontalPadding(horizontalPadding);
}

bool sdlbox::Component::receivePosition() const {
    return true;
}
