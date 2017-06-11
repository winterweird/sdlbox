#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    window.add(new Label("Text on mah label"));

    mainloop(&window);

    return 0;
}
