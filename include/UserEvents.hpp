#ifndef INCLUDE_USEREVENTS_HPP_HEADER_GUARD_40091471521226
#define INCLUDE_USEREVENTS_HPP_HEADER_GUARD_40091471521226

#include <string>
#include <map>

namespace sdlbox {
    class UserEvents {
        public:
            static bool eventRegistered(std::string name);
            static unsigned int eventCode(std::string name);
            static unsigned int existingEventCode(std::string name);
        private:
            static std::map<std::string, int> eventCodes;
    };
}

#endif /* INCLUDE_USEREVENTS_HPP_HEADER_GUARD_40091471521226 */
