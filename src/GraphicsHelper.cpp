#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include <string>
#include <iostream>

using std::string;
using std::runtime_error;

sdlbox::Font* sdlbox::GraphicsHelper::defaultFont = NULL;

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

sdlbox::Font* sdlbox::GraphicsHelper::getDefaultFont() {
    if (defaultFont != NULL) {
        return defaultFont;
    }

    string options[] = {"default.ttf", "calibri.ttf", "arial.ttf", "times.ttf"};

    for (auto opt : options) {
        try {
            defaultFont = new Font(opt, 20);
            return defaultFont;
        } catch (const runtime_error &err) {
            // move on to next option
            // also, I should create custom exceptions...
        }
    }

    throw runtime_error("Error loading default font: No font file found");
}
