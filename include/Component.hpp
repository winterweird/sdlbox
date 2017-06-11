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

            void setPosition(int x, int y);
            void setPosition(Component* relative, int x, int y);

            // whether or not the specified component should receive its
            // position from its parent or not
            virtual bool receivePosition() const;
            
            virtual void draw() const = 0;
        private:
            int x, y;
    };
}

#endif /* INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708 */
