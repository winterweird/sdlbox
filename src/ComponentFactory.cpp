#include "ComponentFactory.hpp"
#include <iostream> // testing
#include <algorithm> // min, max

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

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateX(double dx) {
    return updatePosition(dx, 0);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateX(double dx, double minValue, double maxValue) {
    return updateX(dx, minValue, maxValue, []{});
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateX(double dx, double minValue, double maxValue, std::function<void()> oncap) {
    double change = std::max(minValue - component->x, std::min(dx, maxValue - component->x));
    if (change != dx) {
        oncap();
    }
    return updateX(change);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateY(double dy) {
    return updatePosition(0, dy);
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateY(double dy, double minValue, double maxValue) {
    return updateY(dy, minValue, maxValue, []{});
}

sdlbox::ComponentFactory& sdlbox::ComponentFactory::updateY(double dy, double minValue, double maxValue, std::function<void()> oncap) {
    double change = std::max(minValue - component->y, std::min(dy, maxValue - component->y));
    if (change != dy) {
        oncap();
    }
    return updateY(change);
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
