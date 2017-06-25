# class Component

## ToC:

[Description](#description)

[Public methods](#public-methods)

* virtual ~Component
* virtual int getWidth() const = 0
* virtual int getHeight() const = 0
* virtual int getX() const
* virtual int getY() const
* virtual bool receivePosition() const

* SDL_Rect getRect() const
* virtual bool collides(Component* other) const

* int getVerticalPadding() const
* int getHorizontalPadding() const
* int getLeftPadding() const
* int getRightPadding() const
* int getTopPadding() const
* int getBottomPadding() const
* void getPadding(int &lPad, int &rPad, int &tPad, int &bPad) const

* int getZLevel() const

* virtual bool drawable() const
* virtual void draw() const = 0
* virtual bool operator<(Component* other) const

* virtual void handle(const SDL_Event &e)
* virtual void step()
* virtual void commit()

* void addEventListener(int eventType, EventListener* l)
* void clearEventListeners(int eventType)

## Description

TODO: Description

## Public methods

### ~Component

Destructor. Frees all EventListeners added to the Component.

### int getWidth()

Returns the width of the Component, in pixels. Must be overridden in subclasses.

### int getHeight()

Returns the height of the Component, in pixels. Must be overridden in subclasses.

### int getX()

Returns the X coordinate of the topleft corner of the Component (absolute with regards to the visible screen).

### int getY()

Returns the Y coordinate of the topleft corner of the Component (absolute with regards to the visible screen).

### SDL_Rect getRect()

Convenience method: Returns an SDL_Rect based on the information returned by getX, getY, getWidth and getHeight. This rect can thereafter be used directly in SDL API methods.

### bool collides(Component* other)

Convenience method: Checks whether the rectangles of any two Components intersect (uses SDL's SDL_IntersectRect function).

### int getVerticalPadding()

Convenience method: Returns getTopPadding() + getBottomPadding(). Useful when calculating how much vertical space the Component will take altogether.

### int getHorizontalPadding()

Convenience method: Returns getLeftPadding() + getRightPadding(). Useful when calculating how much horizontal space the Component will take altogether.

### int getLeftPadding()

Return the amount of empty space that should be left to the left of this Component.

Note that there is no distinction between "padding" and "margin" of Components, unlike in CSS. Both refer to empty space around the Component - as such, they share more similarities with what would in CSS be called "margin". If the component contains other Components, it's possible to emulate a CSS "padding" in the outer component by setting the inner Component's padding to some value.

### int getRightPadding()

Return the amount of empty space that should be left to the right of this Component.

Note that there is no distinction between "padding" and "margin" of Components, unlike in CSS. Both refer to empty space around the Component - as such, they share more similarities with what would in CSS be called "margin". If the component contains other Components, it's possible to emulate a CSS "padding" in the outer component by setting the inner Component's padding to some value.

### int getTopPadding()

Return the amount of empty space that should be left above this Component.

Note that there is no distinction between "padding" and "margin" of Components, unlike in CSS. Both refer to empty space around the Component - as such, they share more similarities with what would in CSS be called "margin". If the component contains other Components, it's possible to emulate a CSS "padding" in the outer component by setting the inner Component's padding to some value.

### int getBottomPadding()

Return the amount of empty space that should be left below this Component.

Note that there is no distinction between "padding" and "margin" of Components, unlike in CSS. Both refer to empty space around the Component - as such, they share more similarities with what would in CSS be called "margin". If the component contains other Components, it's possible to emulate a CSS "padding" in the outer component by setting the inner Component's padding to some value.

### void getPadding(int &lPad, int &rPad, int &tPad, int &bPad)

Convenience method: Simultaneously retrieve and store the padding space on each side of the Component with a ##single method call.

### int getZLevel()

Return the Z level of the Component, which determines draw order: The lower the Z level, the earlier the Component is drawn, meaning that other components drawn at a later point will be drawn "on top" of it.

### bool drawable()

Returns whether the Component should be drawn to the screen: Some components are not intended to be drawn in any way, and their draw methods need not be called, nor do they need to be sorted according to draw order.

### void draw()

Draws the Component to the screen, presumably at its given position and with its given size. Must be overridden in subclasses.

### bool operator<(Component* other)

Used for sorting Components according to draw order. By default, Components are sorted by a Z level instance variable, but this behavior may be overridden in subclassing Components.

### void handle(const SDL_Event &e)

Handles an SDL event. By default, this method goes through all the EventListeners for the given event type and performs their action (if there is a match)

see [EventListener](EventListener.md)

### void step()

Method which is executed every step in the program's main loop. This is useful for handling stuff which happens constantly, such as for instance animation updates (although animation is currently not implemented), as well as stuff such as continuous key presses.

### void commit()

Method used for propagating changes made to a Component downward in the inheritance hierarchy. This method can be called by methods which only know they are looking at a Component, and be overridden in subclasses to produce the desired behavior. A prime example would be how commit is called after ComponentFactory updates a Component's position - this change is propagated down through subclasses such as for instance TextureComponent, which repositions its internal Texture relative to its own position.

### void addEventListener(int eventType, EventListener* l)

Adds an EventListener which contains an action as well as (optionally) a predicate specifying the conditions for executing the action. The EventListener is associated with a specific type of SDL event - this could be either a standard SDL event, or a custom user-defined event.

see [EventListener](EventListener.md), [UserEvents](UserEvents.md)

### void clearEventListeners(int eventType)

Removes and frees all the registered events for a given event type. There is (currently) no way of removing a specific EventListener - if you want to remove one, you have to remove all other listeners of the same type registered by the Component as well.

TODO: add formatting to ToC and headers, and header anchors to ToC.

TODO: write out API overview for more classes and [create general overview](/../../edit/master/docs/OVERVIEW.md)
