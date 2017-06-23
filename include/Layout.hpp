#ifndef INCLUDE_LAYOUT_HPP_HEADER_GUARD_54872562832370
#define INCLUDE_LAYOUT_HPP_HEADER_GUARD_54872562832370

namespace sdlbox {
    class Layout {
        public:
            static const int VERTICAL = 0;
            static const int HORIZONTAL = 1;

            static const int CENTER      =  0;
            static const int TOP         =  1;
            static const int BOTTOM      = -1;
            static const int LEFT        = -3;
            static const int RIGHT       =  3;
            static const int TOPLEFT     = TOP + LEFT;     // -2
            static const int TOPRIGHT    = TOP + RIGHT;    //  4
            static const int BOTTOMLEFT  = BOTTOM + LEFT;  // -4
            static const int BOTTOMRIGHT = BOTTOM + RIGHT; //  2
            // Rules:
            // n > 1  -> RIGHT
            // n < -1 -> LEFT
            // n + 2 % 3 == 0 -> TOP
            // n - 2 % 3 == 0 -> BOTTOM
            // Also, this is horrible and people should never do this
        private:
    };
}

#endif /* INCLUDE_LAYOUT_HPP_HEADER_GUARD_54872562832370 */
