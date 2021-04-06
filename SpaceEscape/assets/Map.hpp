#pragma once
#include <stdint.h>
#include <vector>

#include "StationTiles.hpp"

/* StationTiles.hpp */


/* End StationTiles.hpp */

#define TILE_SIZE 16

#define NUM_DIRECTIONS 4

enum Direction {UP, RIGHT, DOWN, LEFT};

Direction dir_opposit(Direction);

typedef struct {
    uint8_t x;
    uint8_t y;
} pos_t;

const pos_t null_pos = { 0, 0 };

typedef struct {
    pos_t position;
    uint8_t* sprite;
} asset_t;

/**
 * Room to be used in combination with effects and pointers to other rooms to make 
 * a Room. All maps are static and compiled
 * */
class Room {
public:
    const uint8_t width;        // Tilemap width
    const uint8_t height;       // Tilemap height
    pos_t spawn_fallback;
    const uint8_t* entrances;     // Entrances to scene (x pos of left/right and y pos of up/down are implicit)
    const uint8_t* tilemap;
    std::vector<asset_t> assets;

    Room(uint8_t width, uint8_t height, const uint8_t* entrances, const uint8_t* tilemap);
    Room(uint8_t width, uint8_t height, pos_t spawnpoint, const uint8_t* entrances, const uint8_t* tilemap);
    //Room(uint8_t width, uint8_t height, const uint8_t* entrances, const uint8_t* tilemap);

    bool has_entrance(Direction) const;
    // Return tileId spawn position (multiply with TILE_SIZE to get render position)
    pos_t get_entrance(Direction) const;
};

// Room

