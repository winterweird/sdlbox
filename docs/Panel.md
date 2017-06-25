# class Panel

## ToC:

[Description](#description)

[Public methods](#public-methods)

* [`Panel(int orientation)`](#panelint-orientation)
* [`~Panel()`](#panel)

* [`void add(Component* c)`](#void-addcomponent-c)

* [`int getWidth()`](#int-getwidth)` const override`
* [`int getHeight()`](#int-getheight)` const override`

* [`void draw()`](#void-draw)` const override`

* [`void commit()`](#void-commit)` override`

* [`void step()`](#void-step)` override`

[Private methods](#private-methods)

* [`void repositionChildren()`](#void-repositionchildren)

## Description

The Panel class is a container class which can contain Components, manages
their positions and administers their interactions with the program from above.
It is responsible for drawing all the Components and executing their step
methods, as well as updating their positions when outside changes occur (see
[commit](#void-commit)).

It shares a similar ([albeit distinct](SDLBox.md#design-decisions)) interface
with SDLBox, which is also a container of Components.

## Public methods

### `Panel(int orientation)`

Constructor. Parameter determines whether Components added to the Panel are
positioned horizontally or vertically, and should be one of the
[Layout](Layout.md) constants `Layout::HORIZONTAL` or `Layout::VERTICAL`.

To get a more complex layout, you may try nested Panels altering between
horizontal and vertical layout.

### `~Panel()`

Destructor. Frees all the child Components it contains, which in turn free the
resources they are responsible for managing.

### `void add(Component* c)`

Adds a Component to the Panel. The Component is automatically positioned
according to the orientation of the Panel and the padding specified in the
Component.

### `int getWidth()`

Returns the combined width of all the Components the Panel contains, padding
inclusive. If the orientation is vertical, this is equal to the width of the
widest child Component.

### `int getHeight()`

Returns the combined height of all the Components the Panel contains, padding
inclusive. If the orientation is horizontal, this is equal to the height of the
tallest child Component.

### `void draw()`

Draws all the child Components.

NOTE: Does not care about draw order. This is in part because implementing that
is a hassle, and in part because it's already autopositioning all the
Components, so they shouldn't overlap anyways. This, in turn, is because
changing how the code works currently is a hassle, so I guess when it comes down
to it, it's just in full because it's a hassle.

### `void commit()`

Repositions children. Is required because changes in contained Components might
affect the layout of the Panel, and those changes should thus be propagated to
the Panel.

see [repositionChildren](#void-repositionchildren)

### `void step`

Loops through and calls the step method of all its child Components.

## Private methods

### `void repositionChildren()`

Helper method: Recalculates and updates the position of its children, as well as
the new total width and height of the Panel.
