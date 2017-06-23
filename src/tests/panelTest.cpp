#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    Panel* p1 = new Panel(Layout::VERTICAL);
    Panel* p2 = new Panel(Layout::HORIZONTAL);
    Panel* p3 = new Panel(Layout::VERTICAL);
    
    p1->add(new Label("With some text"));
    p1->add(new Label("Starting to lose creativity here..."));
    
    p2->add(new Label("With some more text"));
    p2->add((new Label("With even more text"))->withHPad(20));
    p2->add(new Label("MAGIC"));
    
    
    p3->add(new Label("Only text"));
    p3->add(new Label("More only text"));

    window.add(p1);
    window.add(p2);
    window.add(p3);

    mainloop(&window);

    return 0;
}
