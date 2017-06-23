#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Sample program 101");

    int i = 0;

    Panel* counterPane = new Panel(Layout::HORIZONTAL);
    counterPane->add(new Label("Counter:"));
    
    Label* c = new VolatileLabel(to_string(i)); // volatile labels change often
    counterPane->add(c);

    window.add(counterPane);
    
    auto incr = [&](const SDL_Event &e) {
        c->setText(to_string(++i));
    };
    Button* iButton = new Button("Increment", incr);
    window.add(iButton);

    auto decr = [&](const SDL_Event &e) {
        c->setText(to_string(--i));
    };
    Button* dButton = new Button("Decrement", decr);
    window.add(dButton);
    
    // Actually, the SDL event queue maxes out after 2^16 events. The actual
    // number of button click events simulated is even lower, probably due to
    // the fact that there are already other events in the queue (simply because
    // starting up an SDL program seems to generate some events somehow), so the
    // counter is only incremented up until 65531
    SDL_Event events[100000]; 
    for (SDL_Event e : events) {
        e.type = SDL_MOUSEBUTTONDOWN;
        e.button.button = SDL_BUTTON_LEFT;
        e.button.x = iButton->getX() + 5;
        e.button.y = iButton->getY() + 5;
        SDL_PushEvent(&e);
    }

//    window.continuallyFitToContent();
    window.ctrlWToQuit();
    
    // add to optimize (even if only a little) - will negate continuallyFitToContent
//    window.freezeSize();
    
    mainloop(&window);

    return 0;
}
