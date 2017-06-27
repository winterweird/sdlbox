#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    Panel* p1 = new Panel(Layout::VERTICAL);
    Panel* p2 = new Panel(Layout::HORIZONTAL);
    Panel* p3 = new Panel(Layout::VERTICAL);
    
//    window.add(p1);
//    window.add(p2);
//    window.add(p3);
    
    p1->add(new Label("With some text"));
    p1->add(new Label("Starting to lose creativity here..."));
    
    p2->add(new Label("With some more text"));
    p2->add(ComponentFactory(new Label("With even more text")).hpad(20).create());
    p2->add(new Label("MAGIC"));
    
    p3->add(new Label("Only text"));
    p3->add(new Label("More only text"));
    
    // For some reason I have to add these to window only AFTER I've filled them
    // with crap. I have no idea why.
    window.add(p1);
    window.add(p2);
    window.add(p3);

    window.scheduleReposition();
    mainloop(&window);

    return 0;
}
