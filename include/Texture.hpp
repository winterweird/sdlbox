#ifndef INCLUDE_TEXTURE_HPP_HEADER_GUARD_109521511612734
#define INCLUDE_TEXTURE_HPP_HEADER_GUARD_109521511612734

#include "Component.hpp"
#include <SDL2/SDL.h>

namespace sdlbox {
    class Texture : public Component {
        public:
            Texture(SDL_Texture* texture, int w, int h);
            ~Texture();
            
            int getWidth() const override;
            int getHeight() const override;

            void draw() const override;
        private:
            int width, height;
            SDL_Texture* texture;
    };
}

#endif /* INCLUDE_TEXTURE_HPP_HEADER_GUARD_109521511612734 */
