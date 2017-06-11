#ifndef INCLUDE_FONT_HPP_HEADER_GUARD_135412431520899
#define INCLUDE_FONT_HPP_HEADER_GUARD_135412431520899

#include <string>
#include <SDL2/SDL_ttf.h>
#include "Color.hpp"
#include "Texture.hpp"

namespace sdlbox {
    class Font {
        public:
            Font(std::string filename, int size);
            ~Font();

            Texture* render(std::string text, const Color &color);
            Texture* renderBlended(std::string text, const Color &color);
            Texture* renderShaded(std::string text, const Color &fgColor, const Color &bgColor);

            int getTextWidth(std::string text) const;
            int getTextHeight(std::string text) const;

            void getTextDimensions(std::string text, int& width, int& height) const;
        private:
            TTF_Font* font;
    };
}

#endif /* INCLUDE_FONT_HPP_HEADER_GUARD_135412431520899 */
