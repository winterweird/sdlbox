#include "sdlbox.hpp"
#include <thread>
#include <atomic>

void sdlbox::mainloop(sdlbox::SDLBox* window) {
    SDL_Event e;
    std::atomic<bool> running(true);
    
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
            else {
                window->handle(e);
            }
        }
    }

    t.join();
}
