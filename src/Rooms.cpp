#include "Rooms.hpp"

using std::runtime_error;

std::map<std::string, int> sdlbox::Rooms::rooms;

void sdlbox::Rooms::addRoom(const std::string &roomName) {
    if (rooms.find(roomName) != rooms.end())
        throw runtime_error("Error adding room: room " + roomName + " already exists");

    rooms[roomName] = Room::class_id++;
}

sdlbox::Room sdlbox::Rooms::getRoom(const std::string &roomName) {
    if (roomName == "DEFAULT")
        return Room(); // default room
    
    auto r = rooms.find(roomName);
    if (r == rooms.end()) {
        throw runtime_error("Error getting room " + roomName + ": no such room");
    }

    return Room(r->second);
}

std::string sdlbox::Rooms::getRoomName(const Room &room) {
    if (room.id == -1)
        return "DEFAULT";
    
    for (auto r : rooms) {
        if (r.second == room.id) {
            return r.first;
        }
    }

    throw runtime_error("No room name found corresponding to given id");
}
