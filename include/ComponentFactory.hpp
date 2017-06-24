#ifndef INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741
#define INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741

#include "Component.hpp"

namespace sdlbox {
    class ComponentFactory {
        public:
            ComponentFactory(Component* c);

            ComponentFactory& autoposition(bool state=true);
            ComponentFactory& position(int x, int y, int anchor=Layout::TOPLEFT);
            ComponentFactory& position(Component* relative, int x, int y, int anchor=Layout::TOPLEFT);
            
            ComponentFactory& zLevel(int level);

            Component* create() const;
        private:
            Component* component;
    };
}

#endif /* INCLUDE_COMPONENTFACTORY_HPP_HEADER_GUARD_2694066718741 */
