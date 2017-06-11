#ifndef INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912
#define INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912

#include "Component.hpp"
#include <vector>

namespace sdlbox {
    class Panel : public Component {
        public:
            void add(Component* c);
            int getWidth() const override;
            int getHeight() const override;
        private:
            std::vector<Component*> components;
            int width, height;
    };
}

#endif /* INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912 */
