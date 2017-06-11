#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    sdlbox::SDLBox window("Window title");

    mainloop(&window);

    return 0;
}
