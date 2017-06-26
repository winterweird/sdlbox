# class TextureComponent

## ToC:

[Description](#description)

[Public methods](#public-methods)

* [`~TextureComponent()`](#texturecomponent)

* [`int getWidth()`](#int-getwidth)` const override`
* [`int getHeight()`](#int-getheight)` const override`

* [`void draw()`](#void-draw)` const override`

* [`void commit()`](#void-commit)` override`

[Protected methods](#protected-methods)

* [`void setTexture(Texture* t)`](#void-settexturetexture-t)
* [`void repositionTexture(int xOffset, int yOffset)`](#void-repositiontextureint-xoffset-int-yoffset)

## Description

This is a base class for Components which contain a [Texture](Texture.md)
internally. Although it's technically not an abstract class, it's not really
usable unless subclassed, as it does not provide neither a constructor nor any
other way to transform it to a usable Component.

### Design choices

For the most part, it would have been just as good (and possibly better) to
extend Texture directly instead of having a "TextureComponent" as a thin wrapper
to a wrapper to SDL_Texture. However, as I see it, there is one definite
advantage: Abstracted updatability. By extending Texture, the wrapper to
SDL_Texture, directly, I would have to get down and dirty with the SDL API
whenever I'd want to update the Texture. If I abstract this away, then as far as
any user is concerned, they don't really need to worry about the SDL API at all,
because they don't need to touch it directly and can easily work with the sdlbox
API which handles it for them instead.

## Public methods

### `~TextureComponent()`

Destructor. Frees the internal Texture.

### `int getWidth()`

Returns the width of the internal Texture in pixels, or NULL if the Texture has
not been set.

### `int getHeight()`

Returns the height of the internal Texture in pixels, or NULL if the Texture has
not been set.

### `void draw()`

If Texture has been set, calls its draw method.

### `void commit()`

Repositions internal Texture at (0, 0) relative to the TextureComponent
position.

## Protected methods

### `void setTexture(Texture* t)`

Frees the old Texture if it was set, then sets a new one. This is how subclasses
are able to put the TextureComponent's capabilities to use.

### `void repositionTexture(int xOffset, int yOffset)`

If Texture is set, positions the Texture at (xOffset, yOffset) relative to the
TextureComponent position. This is required because the information used by the
draw method to draw the Texture to the screen should be updated in accordance
with the current position of the Component the Texture is contained within.
