#include "sdlbox.hpp"
#include <iostream>
#include <atomic>
#include <mutex>

using namespace sdlbox;
using namespace std;

std::mutex mtx;

int main(int argc, char** argv) {
    SDLBox window("Sample program 101");

    atomic<int> i(0);

    Label* l = new Label("Counter: " + to_string(i));
    window.add(l);

    auto incr = [&](const SDL_Event &e) {
        i++;
        cout << "incr" << i << endl;
        l->setText("Counter: ");
    };
    window.add(new Button("Increment", incr));

    auto decr = [&](const SDL_Event &e) {
        i--;
        cout << "decr" << i << endl;
        l->setText("Counter: ");
    };
    window.add(new Button("Decrement", decr));

    mainloop(&window);

    return 0;
}
