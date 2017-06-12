#ifndef INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993
#define INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993

#include "Component.hpp"
#include "Callback.hpp"
#include "Texture.hpp"
#include <string>

namespace sdlbox {
    class Button : public Component {
        public:
            Button(std::string text, Callback* callback);
            ~Button();

            int getWidth() const override;
            int getHeight() const override;

            Component* withPosition(int x, int y) override;
            Component* withPosition(Component* relative, int x, int y) override;
            
            void draw() const override;

            void handle(const SDL_Event &e) override;
        private:
            Callback* c;
            Texture* texture;
    };
}

#endif /* INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993 */
