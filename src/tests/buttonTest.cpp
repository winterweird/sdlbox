#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    window.setOrientation(Layout::HORIZONTAL);

    int i = 233;
    
    window.add(new Label("Here is some text to make sure stuff works"));
    
    auto callback = [&](const SDL_Event &e) {
        cout << "Heyyyy " << i++ << endl;
    };
    window.add(ComponentFactory(new Button("Button text", callback)).hpad(20).create());
    
    window.add(new Label("And here is some more text"));
    
    mainloop(&window);

    return 0;
}
