#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    window.add(new Label("Text on mah label"));
    window.add(new Label("Another label", Color(0xff, 0, 0xff), true));
    window.add(new Label("A third label", Color(0xff, 0, 0xff), Color(0, 0xff, 0)));

    mainloop(&window);

    return 0;
}
