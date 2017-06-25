# sdlbox

I created this project as a way to get a simple, easy to use C++ interface against the SDL2 API for C/C++. The idea is to let interactions happen via the interface as much as possible, yet it's possible to use only parts of it and/or extend it with direct calls to the SDL2 API if need be.

Refer to the [SDL Wiki](https://wiki.libsdl.org/) for API documentation and the [Lazy Foo' Productions tutorial on SDL](http://lazyfoo.net/tutorials/SDL/) for an introduction to programming with SDL2.

DISCLAIMER: This project is only a personal project which I have started in part to develop my SDL and C++ programming abilities in general, in part for the fun of it, and in part because I wish to reuse this work in later projects of mine. This software is provided as-is, without any guarantees, not even for suitability for a specific purpose. The author claims no responsibility for any effects, intended or unintended, which running this code on someone's computer may or may not produce.

## Downloading and utilizing the code base

### Linux (assumes the make tool and the g++ compiler are installed):

After cloning the repository, you should run `make init` to ensure that all the directories used throughout the build process have been created. After that, run `make` (or `make all`) to build the static library "sdlbox" and the current test program target. You can also specifically build the library by running `make lib/libsdlbox.a`. A precompiled version of the library is included in the lib folder - however, it was built on my computer and I make no guarantees whatsoever that it will be at all usable on any other PC.

When programming with the sdlbox API, include "sdlbox.hpp" in your project. You may add the include folder in this project as an include folder in your project (use `-I<path to folder>` with g++ or refer to the documentation of your compiler of choice), copy the contents of the include folder to wherever you keep your project's includes, or copy its content to the place your system includes are located for easy access in future projects. It should not be necessary to include any other header files than sdlbox.hpp, as all the other parts of the project should be included, either indirectly or directly, by this header, but you are free to exclude the sdlbox.hpp header and instead only include the specific headers you need for your project.

You will also need to link against the sdlbox library as well as the libraries SDL2, SDL2_ttf and pthread. SDL2_image is, as per the current version, not required to link against, but I plan to add this and SDL2_mixer as dependencies in the future. Refer to your compiler's linkage documentation. Note that the sdlbox library will (probably) need to be linked first, as it refers to functions available in the other libraries. Refer to this project's makefile for a linkage order which at least works for me.

### Windows and everything else

I don't really know, and I don't really care. In theory, this code should be cross-platform compatible, provided that you have SDL2 on your platform (and that you can get threads to work somehow), but I'm developing on Linux and I can't be arsed to figure out how to do it elsewhere. Reading the makefile might take you at least part of the way, though.

### Fonts

Note that in order to utilize fonts, you need to find a .ttf font and include it in your project. For simplicity, sdlbox by default utilizes fonts named "default.ttf" and which are placed in either the project root folder or a "res" folder directly under the root folder. There are several fonts out there which are free for commercial and/or personal use, but please pay heed to rules and regulations regarding alteration and/or redistributability. Due to these rules, just to be safe, I've decided not to include any fonts together with the code base.

For my own testing purposes I use [IM Fell French Canon](http://www.1001fonts.com/im-fell-french-canon-font.html) (by [Igino Marini](www.iginomarini.com)), which is readable and come with very few restrictions.

## Extending the project

You're free to reuse and modify any code in this project. You may also add more functionality as you'd like. You may want to read the actual code before proceeding. However, please be mindful of your sanity. Read the code at your own risk, and preferably with breaks as necessary.

## API overview and documentation

The API documentation is far from finished, but a preliminary [overview](docs/OVERVIEW.md) is currently available, and is pointing to each of the API pages which will be updated as soon as I get to it.
