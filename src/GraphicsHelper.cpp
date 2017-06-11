#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include <string>
#include <iostream>

using std::string;
using std::runtime_error;

sdlbox::Texture* sdlbox::GraphicsHelper::createTexture(SDL_Surface* surf, bool freesrc) {
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

    int w = surf->w;
    int h = surf->h;
    
    if (freesrc) {
        SDL_FreeSurface(surf);
    }

    if (texture == NULL) {
        throw runtime_error("Error creating texture from surface: " + string(SDL_GetError()));
    }
    
    return new Texture(texture, w, h);
}
