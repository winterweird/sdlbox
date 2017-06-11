#ifndef INCLUDE_COLOR_HPP_HEADER_GUARD_236321338518905
#define INCLUDE_COLOR_HPP_HEADER_GUARD_236321338518905

#include <SDL2/SDL.h>

namespace sdlbox {
    class Color {
        public:
            Color(int r, int g, int b, int a=0xff);

            SDL_Color toSDLColor() const;
        private:
            SDL_Color color;
    };
}

#endif /* INCLUDE_COLOR_HPP_HEADER_GUARD_236321338518905 */
