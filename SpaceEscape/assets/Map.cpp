#include "Map.h"

Direction dir_opposit(Direction d) {
    return (Direction)(((uint8_t)d+2)%NUM_DIRECTIONS);
}

Room::Room(uint8_t width, uint8_t height, const uint8_t* entrances, const uint8_t* tilemap) :
    width(width),
    height(height),
    entrances(entrances),
    tilemap(tilemap) 
{
    for (uint8_t x = 0; x < width; x++) {
        uint8_t y;
        for (y = 0; y < height; y++) {
            if (WALKABLES.find((StationTile)this->tilemap[y*width + x]) != WALKABLES.end()) {
                this->spawn_fallback = (pos_t){x, y};
                break;
            }
        }
        if (y < height) { break; }
    }
}

Room::Room(uint8_t width, uint8_t height, const pos_t spawnpoint, const uint8_t* entrances, const uint8_t* tilemap) :
    Room(width, height, entrances, tilemap)
{
    this->spawn_fallback = spawnpoint;
}

bool Room::has_entrance(Direction d) const {
    return entrances[d] != 0;
}

pos_t Room::get_entrance(Direction d) const {
    switch (d)
    {
    case Direction::UP:
        return (pos_t){entrances[d]*TILE_SIZE, 0 };
        break;
    case Direction::DOWN:
        return (pos_t){entrances[d]*TILE_SIZE, this->height*TILE_SIZE - TILE_SIZE };
        break;
    case Direction::LEFT:
        return (pos_t){0, entrances[d]*TILE_SIZE};
        break;
    case Direction::RIGHT:
        return (pos_t){this->width*TILE_SIZE - TILE_SIZE, entrances[d]*TILE_SIZE};
        break;
    default:
        return {0, 0};
        break;
    }
}