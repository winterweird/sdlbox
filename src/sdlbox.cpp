#include "sdlbox.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream> // testing

std::condition_variable sdlbox::cv;
bool sdlbox::isDrawing = false;

void sdlbox::mainloop(sdlbox::SDLBox* window) {
    SDL_Event e;
    std::atomic<bool> running(true);
    
    std::thread t([&]() {
        while (running) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{return isDrawing;});
            window->draw();
            isDrawing = false;
            lock.unlock();
            cv.notify_one();
        }
    });

    while (running) {
        auto start = SDL_GetTicks();
        auto end = start;
        auto diff = end-start;
        unsigned int fps = window->getFPS();
        
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{return !isDrawing;});

        while (diff < 1000/fps && SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else {
                window->handle(e);
            }

            end = SDL_GetTicks();
            diff = end-start;
        }
        
        isDrawing = true;
        lock.unlock();
        cv.notify_one();

        if (diff < 1000/fps) {
            SDL_Delay(1000/fps - diff);
        }
    }

    t.join();
}
