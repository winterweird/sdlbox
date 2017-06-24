#include "ComponentFactory.hpp"
#include <iostream> // testing

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
    
    autoposition(false);
    component->commit();
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::position(Component* relative, int x, int y, int anchor) {
    return position(relative->getX() + x, relative->getY() + y, anchor);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::lpad(int amount) {
    component->lPad = amount;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::rpad(int amount) {
    component->rPad = amount;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::tpad(int amount) {
    component->tPad = amount;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::bpad(int amount) {
    component->bPad = amount;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::hpad(int amount) {
    lpad(amount);
    rpad(amount);
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::vpad(int amount) {
    tpad(amount);
    bpad(amount);
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::padding(int vPad, int hPad) {
    tpad(vPad);
    bpad(vPad);
    lpad(hPad);
    rpad(hPad);
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::padding(int lPad, int rPad, int tPad, int bPad) {
    lpad(lPad);
    rpad(rPad);
    tpad(tPad);
    bpad(bPad);
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::zLevel(int level) {
    component->zlvl = level;
    return *this;
}

sdlbox::Component* sdlbox::ComponentFactory::create() const {
    return component;
}
