#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Title");
    
    Font f("default.ttf", 20);
    auto text = f.render("Some text", Color(0xff, 0, 0));
    
    window.add(text);

    mainloop(&window);

    cout << "End" << endl;
    
    return 0;
}
