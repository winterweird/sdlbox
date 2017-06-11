#include "Panel.hpp"
#include <algorithm> // std::max

using std::max;

void sdlbox::Panel::add(Component* c) {
    components.push_back(c);
    
    width = max(c->getWidth(), width);
    height = max(c->getHeight(), height);
}

int sdlbox::Panel::getWidth() const {
    return width;
}

int sdlbox::Panel::getHeight() const {
    return height;
}
