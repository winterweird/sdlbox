#ifndef INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741
#define INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741

#include "Component.hpp"

namespace sdlbox {
    class ComponentFactory {
        public:
            ComponentFactory(Component* c);

            ComponentFactory& autoposition(bool state=true);
            ComponentFactory& position(double x, double y, int anchor=Layout::TOPLEFT);
            ComponentFactory& position(Component* relative, double x, double y, int anchor=Layout::TOPLEFT);
            ComponentFactory& positionX(double x, int anchor=Layout::LEFT);
            ComponentFactory& positionY(double y, int anchor=Layout::TOP);
            
            ComponentFactory& updatePosition(double dx, double dy);
            ComponentFactory& updateX(double dx);
            ComponentFactory& updateX(double dx, double minValue, double maxValue);
            ComponentFactory& updateY(double dy);
            ComponentFactory& updateY(double dy, double minValue, double maxValue);

            ComponentFactory& lpad(int amount);
            ComponentFactory& rpad(int amount);
            ComponentFactory& tpad(int amount);
            ComponentFactory& bpad(int amount);
            ComponentFactory& hpad(int amount);
            ComponentFactory& vpad(int amount);
            ComponentFactory& padding(int vPad, int hPad);
            ComponentFactory& padding(int lPad, int rPad, int tPad, int bPad);
            
            ComponentFactory& zLevel(int level);

            Component* create() const;
        private:
            Component* component;
    };
}

#endif /* INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741 */
