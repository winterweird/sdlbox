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

void sdlbox::GraphicsHelper::drawRoundedRect(SDL_Rect* where, double r, Color color) {
    // What follows is the ugliest code I have written thus far for this
    // project, and I hope I will never have to look at it again.
    
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    SDL_Color c = color.toSDLColor();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    
    // top line
    int x1 = (int)round(where->x + r);
    int y1 = (int)round(where->y);
    int x2 = (int)round(where->x + where->w - r);
    int y2 = y1;
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // bottom line
    y1 = (int)round(where->y + where->h);
    y2 = y1;
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    int right = where->x + where->w; // for safekeeping

    // left line
    x1 = where->x;
    x2 = x1;
    y1 = (int)round(where->y + r);
    y2 = (int)round(where->y + where->h - r);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // right line
    x1 = right; x2 = right; // *feels clever*
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // topleft corner
    int cx = where->x + r;
    int cy = where->y + r;
    for (int i = cx - r; i <= cx; i++) {
        for (int j = cy - r; j <= cy; j++) {
            int xDiff = (cx-i);
            int xSq= xDiff*xDiff;
            int yDiff = (cy-j);
            int ySq= yDiff*yDiff;
            int rSq= (int)round(r*r);
            if (xSq+ ySq<= rSq+(r*1.5) && xSq+ ySq>= rSq-r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    // topright corner
    cx = where->x + where->w - r;
    for (int i = cx; i <= cx+r; i++) {
        for (int j = cy - r; j <= cy; j++) {
            int xDiff = (cx-i);
            int xSq= xDiff*xDiff;
            int yDiff = (cy-j);
            int ySq= yDiff*yDiff;
            int rSq= (int)round(r*r);
            if (xSq+ ySq<= rSq+(r*1.5) && xSq+ ySq>= rSq-r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    // bottomright corner
    cy = where->y + where->h - r;
    for (int i = cx; i <= cx+r; i++) {
        for (int j = cy; j <= cy+r; j++) {
            int xDiff = (cx-i);
            int xSq= xDiff*xDiff;
            int yDiff = (cy-j);
            int ySq= yDiff*yDiff;
            int rSq= (int)round(r*r);
            if (xSq+ ySq<= rSq+(r*1.5) && xSq+ ySq>= rSq-r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    // bottomleft corner
    cx = where->x + r;
    for (int i = cx-r; i <= cx; i++) {
        for (int j = cy; j <= cy+r; j++) {
            int xDiff = (cx-i);
            int xSq= xDiff*xDiff;
            int yDiff = (cy-j);
            int ySq= yDiff*yDiff;
            int rSq= (int)round(r*r);
            if (xSq+ ySq<= rSq+(r*1.5) && xSq+ ySq>= rSq-r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
}
