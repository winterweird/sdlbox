#include "ComponentFactory.hpp"
#include <iostream> // testing

sdlbox::ComponentFactory::ComponentFactory(Component *c) : component(c) { }

sdlbox::ComponentFactory& sdlbox::ComponentFactory::autoposition(bool state) {
    component->rcvPos = state;
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::position(double x, double y, int anchor) {
    positionX(x, anchor);
    positionY(y, anchor);
    
    autoposition(false);
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::position(Component* relative, double x, double y, int anchor) {
    return position(relative->getX() + x, relative->getY() + y, anchor);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updatePosition(double dx, double dy) {
    component->x += dx;
    component->y += dy;
    component->commit();
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::positionX(double x, int anchor) {
    if (anchor < -1);
    else if (anchor > 1)
        x -= component->getWidth();
    else
        x -= component->getWidth()/2.0;

    component->x = x;
    component->commit();
    return *this;
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::positionY(double y, int anchor) {
    if ((anchor + 2) % 3 == 0);
    else if ((anchor - 2) % 3 == 0)
        y -= component->getHeight();
    else
        y -= component->getHeight()/2.0;

    component->y = y;
    component->commit();
    return *this;
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
