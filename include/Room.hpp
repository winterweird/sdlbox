#ifndef INCLUDE_ROOM_HPP_HEADER_GUARD_13153137103286
#define INCLUDE_ROOM_HPP_HEADER_GUARD_13153137103286

#include <string>


namespace sdlbox {
    class Rooms; // fwd decl
    
    class Room {
        public:
            Room(std::string roomName);
            bool operator==(const std::string &roomName);
            bool operator==(const Room &other);
            friend class Rooms;
        private:
            Room(int id);
            int id;
            static int class_id;
    };
}

#endif /* INCLUDE_ROOM_HPP_HEADER_GUARD_13153137103286 */
