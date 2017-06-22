#include "Room.hpp"
#include "Rooms.hpp"

int sdlbox::Room::class_id = 0;

sdlbox::Room::Room(std::string roomName) {
    Room r = Rooms::getRoom(roomName);
    this->id = r.id;
}

sdlbox::Room::Room(int id) : id(id) {}

bool sdlbox::Room::operator==(const std::string &roomName) {
    return (*this) == Rooms::getRoom(roomName);
}

bool sdlbox::Room::operator==(const Room &other) {
    return this->id == other.id;
}
