#ifndef INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912
#define INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912

#include "Component.hpp"
#include <vector>

namespace sdlbox {
    class Panel : public Component {
        public:
            Panel(int orientation);
            ~Panel();
            
            void add(Component* c);
            
            int getWidth() const override;
            int getHeight() const override;

            Component* withPosition(int x, int y) override;
            Component* withPosition(Component* relative, int x, int y) override;
            
            void draw() const override;
        private:
            std::vector<Component*> components;
            int width, height;
            int nextX = 0;
            int nextY = 0;
            int orientation;

            void repositionChildren();
    };
}

#endif /* INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912 */
