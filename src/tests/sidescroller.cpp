#include "sdlbox.hpp"
#include <iostream>

using namespace std;
using namespace sdlbox;

int main(int argc, char** argv) {
    SDLBox window("Side scroller - first attempt", 800, 300);

    window.ctrlWToQuit();

    mainloop(&window);

    return 0;
}
