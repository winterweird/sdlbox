#include "EventListener.hpp"

sdlbox::EventListener::EventListener(std::function<void (const SDL_Event &)> c) : callback(c) { }
sdlbox::EventListener::EventListener(std::function<bool (const SDL_Event &)> m,
        std::function<void (const SDL_Event &)> c) : callback(c),  match(m){}

sdlbox::EventListener::~EventListener() { }

void sdlbox::EventListener::handle(const SDL_Event &e) {
    if (match(e))
        callback(e);
}
