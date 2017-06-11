#include "SDLBox.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm> // std::max

using std::string;
using std::runtime_error;
using std::max;

sdlbox::SDLBox* sdlbox::SDLBox::instance = NULL;

sdlbox::SDLBox::SDLBox(string title, int width, int height) : width(width), height(height) {
    init(title);
}

sdlbox::SDLBox::~SDLBox() {
    // destroy all children
    using namespace std;
    for (auto c : components) {
        cout << "Deleting component " << c << endl;
        delete c;
        cout << "Component deleted" << endl;
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlbox::SDLBox::setOrientation(int orientation) {
    this->orientation = orientation;
}

void sdlbox::SDLBox::add(Component* c) {
    components.push_back(c);

    if (c->receivePosition()) {
        c->setPosition(nextX, nextY);
        if (orientation == Layout::VERTICAL) {
            nextY += c->getHeight();
        }
        else if (orientation == Layout::HORIZONTAL) {
            nextX += c->getWidth();
        }
        // else: idk
    }

    if (autoResizeWidth || autoResizeHeight) {
        int w = width;
        int h = height;
        
        if (autoResizeWidth) {
            w = max(c->getX() + c->getWidth(), w);
        }
        if (autoResizeHeight) {
            h = max(c->getY() + c->getHeight(), h);
        }

        resize(w, h);
    }
}

void sdlbox::SDLBox::draw() const {
    SDL_RenderClear(renderer);

    using namespace std;
    for (auto c : components) {
        cout << "ayy" << endl;
        c->draw();
        cout << "eyy" << endl;
    }

    SDL_RenderPresent(renderer);
}

sdlbox::SDLBox* sdlbox::SDLBox::getInstance() {
    if (instance == NULL) {
        throw runtime_error("Cannot get instance: no window has been created");
    }
    return instance;
}

SDL_Renderer* sdlbox::SDLBox::getRenderer() const {
    return renderer;
}

void sdlbox::SDLBox::init(string title) {
    if (instance) {
        throw runtime_error("Cannot start a new SDLBox - another is running");
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw runtime_error("SDL init error: " + string(SDL_GetError()));
    }

    // TODO: Simply passing width/height to the window like this is broken if we
    // operate with variable sized windows. I need to fix that.
    
    if (width <= 0) {
        autoResizeWidth = true;
        width = 1;
    }
    if (height <= 0) {
        autoResizeHeight = true;
        height = 1;
    }
    
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        throw runtime_error("SDL window create error: " + string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        throw runtime_error("SDL renderer create error: " + string(SDL_GetError()));
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // TODO: also initialize image and sound modules
    if (TTF_Init() == -1) {
        throw runtime_error("TTF init error: " + string(TTF_GetError()));
    }

    instance = this;
}

void sdlbox::SDLBox::resize(int w, int h) {
    if (w <= 0 || h <= 0) {
        throw runtime_error("Width/height must be greater than 0");
    }
    
    SDL_SetWindowSize(window, w, h);
    
    width = w;
    height = h;
}
