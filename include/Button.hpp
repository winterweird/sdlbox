#ifndef INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993
#define INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993

#include "Component.hpp"
#include "Texture.hpp"
#include "Label.hpp"
#include <string>
#include <functional>

namespace sdlbox {
    class Button : public Label {
        public:
            using Label::withPosition;
            
            Button(std::string text, std::function<void (const SDL_Event&)> callback);
            Button(std::string text, std::function<bool (const SDL_Event&)> match,
                    std::function<void (const SDL_Event&)> callback);

            int getWidth() const override;
            int getHeight() const override;
            
            void commit() override;
            
            void draw() const override;
        private:
    };
}

#endif /* INCLUDE_BUTTON_HPP_HEADER_GUARD_193223011420993 */
