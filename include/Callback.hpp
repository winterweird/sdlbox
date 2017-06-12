#ifndef INCLUDE_CALLBACK_HPP_HEADER_GUARD_271723542994
#define INCLUDE_CALLBACK_HPP_HEADER_GUARD_271723542994

namespace sdlbox {
    class Callback {
        public:
            virtual ~Callback() {}
            virtual void callback() = 0;
    };
}

#endif /* INCLUDE_CALLBACK_HPP_HEADER_GUARD_271723542994 */
