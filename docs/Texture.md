# class Texture

## ToC:

[Description](#description)

[Public methods](#public-methods)

* [`Texture(SDL_Texture* texture, int w, int h)`](#texturesdl_texture-texture-int-w-int-h)
* [`~Texture()`](#texture)

* [`int getWidth()`](#int-getwidth)` const override`
* [`int getHeight()`](#int-getheight)` const override`

* [`void draw()`](#void-draw)` const override`

## Description

This is a wrapper for the SDL API's [SDL_Texture](https://wiki.libsdl.org/SDL_Texture),
and contains a destructor for automatic cleanup of said texture once the object
is destroyed. It also has all properties of a [Component](Component.md),
including an ability to retrieve the width and height of the texture (something
which is oddly absent from the SDL_Texture itself) and to draw itself to the
screen (using calls to its [draw method](#void-draw)).

## Public methods

### `Texture(SDL_Texture* texture, int w, int h)`

Constructor. Accepts an allocated [SDL_Texture](https://wiki.libsdl.org/SDL_Texture)
as well as a width and a height, and stores these values internally.

### `~Texture()`

Destructor. Destroys the internal texture by calling
[SDL_DestroyTexture](SDL_DestroyTextur://wiki.libsdl.org/SDL_DestroyTexture).

### `int getWidth()`

Returns the width of the texture, in pixels.

### `int getHeight()`

Returns the height of the texture, in pixels.

### `void draw()`

Draws the texture to the screen using the
[SDL_Renderer](https://wiki.libsdl.org/SDL_Renderer) allocated by
[SDLBox](SDLBox.md).
