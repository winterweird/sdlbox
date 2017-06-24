#include "ComponentFactory.hpp"

sdlbox::ComponentFactory::ComponentFactory(Component *c) : component(c) { }

sdlbox::ComponentFactory& sdlbox::ComponentFactory::autoposition(bool state) {
    component->rcvPos = state;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::position(int x, int y, int anchor) {
    if (anchor < -1);
    else if (anchor > 1)
        x -= component->getWidth();
    else
        x -= component->getWidth()/2;
    
    if ((anchor + 2) % 3 == 0);
    else if ((anchor - 2) % 3 == 0)
        y -= component->getHeight();
    else
        y -= component->getHeight()/2;
    
    component->x = x;
    component->y = y;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::position(Component* relative, int x, int y, int anchor) {
    return position(relative->getX() + x, relative->getY() + y, anchor);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::zLevel(int level) {
    component->zlvl = level;
    return *this;
}

sdlbox::Component* sdlbox::ComponentFactory::create() const {
    return component;
}
