#ifndef INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708
#define INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708

namespace sdlbox {
    class Component {
        public:
            virtual ~Component();
            
            virtual int getWidth() const = 0;
            virtual int getHeight() const = 0;

            virtual int getX() const;
            virtual int getY() const;

            virtual void setPosition(int x, int y);
            virtual void setPosition(Component* relative, int x, int y);

            virtual int getVerticalPadding() const;
            virtual int getHorizontalPadding() const;

            virtual void setVerticalPadding(int amount);
            virtual void setHorizontalPadding(int amount);
            virtual void setPadding(int verticalPadding, int horizontalPadding);

            // whether or not the specified component should receive its
            // position from its parent or not
            virtual bool receivePosition() const;
            
            virtual void draw() const = 0;
        private:
            int x, y;
            int vPad = 0, hPad = 0;
    };
}

#endif /* INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708 */
