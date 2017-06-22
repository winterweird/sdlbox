#ifndef INCLUDE_ROOMS_HPP_HEADER_GUARD_8963730815485
#define INCLUDE_ROOMS_HPP_HEADER_GUARD_8963730815485

#include <string>
#include <map>
#include "Room.hpp"

namespace sdlbox {
    class Rooms {
        public:
            static void addRoom(const std::string &roomName);
            static Room getRoom(const std::string &roomName);
        private:
            static std::map<std::string, int> rooms;
    };
}

#endif /* INCLUDE_ROOMS_HPP_HEADER_GUARD_8963730815485 */
