#ifndef INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912
#define INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912

#include "Component.hpp"
#include <vector>

namespace sdlbox {
    class Panel : public Component {
        public:
            using Component::withPosition;
            
            Panel(int orientation);
            ~Panel();
            
            void add(Component* c);
            
            int getWidth() const override;
            int getHeight() const override;

            void draw() const override;

            void handle(const SDL_Event &e) override;
            void step() override;
        private:
            std::vector<Component*> components;
            int width = 1, height = 1;
            int nextX = 0;
            int nextY = 0;
            int orientation;

            void repositionChildren();
    };
}

#endif /* INCLUDE_PANEL_HPP_HEADER_GUARD_151032287726912 */
