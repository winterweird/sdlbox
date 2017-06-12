#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

auto always = [](const SDL_Event &e) {
    return true;
};

auto never = [](const SDL_Event &e) {
    return false;
};

int main(int argc, char** argv) {
    SDLBox window("Sample program 101");

    int i = 0;
    
    Panel* counterPane = new Panel(Layout::HORIZONTAL);
    counterPane->add(new Label("Counter:"));
    Label* c = static_cast<Label*>((new Label(to_string(i)))->withRPad(40));
    counterPane->add(c);

    window.add(counterPane);
    
    auto incr = [&](const SDL_Event &e) {
        c->setText(to_string(++i));
    };
    window.add(new Button("Increment", incr));

   auto decr = [&](const SDL_Event &e) {
        c->setText(to_string(--i));
    };
    window.add(new Button("Decrement", decr));

    mainloop(&window);

    return 0;
}
