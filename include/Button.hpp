#ifndef INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993
#define INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993

#include "Component.hpp"
#include "Texture.hpp"
#include <string>
#include <functional>

namespace sdlbox {
    class Button : public Component {
        public:
            Button(std::string text, std::function<void (const SDL_Event&)> callback);
            Button(std::string text, std::function<bool (const SDL_Event&)> match,
                    std::function<void (const SDL_Event&)> callback);
            ~Button();

            int getWidth() const override;
            int getHeight() const override;

            Component* withPosition(int x, int y) override;
            Component* withPosition(Component* relative, int x, int y) override;
            
            void draw() const override;
        private:
            Texture* texture;
    };
}

#endif /* INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993 */
