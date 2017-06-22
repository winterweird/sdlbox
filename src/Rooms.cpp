#include "Rooms.hpp"

using std::runtime_error;

void sdlbox::Rooms::addRoom(const std::string &roomName) {
    if (rooms.find(roomName) != rooms.end())
        throw runtime_error("Error adding room: room " + roomName + " already exists");

    rooms[roomName] = Room::class_id++;
}

sdlbox::Room sdlbox::Rooms::getRoom(const std::string &roomName) {
    auto r = rooms.find(roomName);
    if (r == rooms.end()) {
        throw runtime_error("Error getting room " + roomName + ": no such room");
    }

    return Room(r->second);
}
