#ifndef INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331
#define INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331

#include <SDL2/SDL.h>
#include "Texture.hpp"

namespace sdlbox {
    // contains nifty little static helper methods
    class GraphicsHelper {
        public:
            static Texture* createTexture(SDL_Surface* surf, bool freesrc=true);
        private:
    };
}

#endif /* INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331 */
