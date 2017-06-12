#ifndef INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331
#define INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Font.hpp"
#include "Color.hpp"

namespace sdlbox {
    // contains nifty little static helper methods
    class GraphicsHelper {
        public:
            static void drawRoundedRect(SDL_Rect* where, double curveRadius, Color color);
            static Texture* createTexture(SDL_Surface* surf, bool freesrc=true);
            static Font* getDefaultFont(); // pointer because copying fonts is scary
        private:
            static Font* defaultFont;
    };
}

#endif /* INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331 */
