#include "Map.h"

Map::Map(uint8_t width, uint8_t height, uint8_t entrances, const uint8_t* tilemap) :
    width(width),
    height(height),
    entrances(entrances),
    tilemap(tilemap) {}

bool Map::has_entrance(Direction d) {
    return (bool)(entrances & d);
}