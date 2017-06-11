#include "sdlbox.hpp"
#include <thread>

void sdlbox::mainloop(sdlbox::SDLBox* window) {
    SDL_Event e;
    bool running = true;
    
    std::thread t([&]() {
        while (running) {
            window->draw();
        }
    });

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        // else: find out what to do
        }
    }

    t.join();
}
