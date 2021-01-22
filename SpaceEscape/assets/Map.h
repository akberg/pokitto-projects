#pragma once
#include <stdint.h>

#include "StationTiles.h"

enum Direction {UP=0, DOWN=1, LEFT=2, RIGHT=4};

/**
 * Map to be used in combination with effects and pointers to other rooms to make 
 * a Room. All maps are static and compiled
 * */
class Map {
public:
    const uint8_t width;        // Tilemap width
    const uint8_t height;       // Tilemap height
    const uint8_t entrances;     // Directions with entrance to scene (bit flags)
    const uint8_t* tilemap;

    Map(uint8_t width, uint8_t height, uint8_t entrances, const uint8_t* tilemap);

    bool has_entrance(Direction);
};

// Map

const uint8_t map0[] = {
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    INN_UR, EDGE_D, EDGE_D, EDGE_D, CRNR_DR,FLOOR0, CRNR_DL,EDGE_D, INN_UL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, CRNR_UL,EDGE_U, CRNR_UR,FLOOR0, CRNR_UL,EDGE_U, OUT_DL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OUT_DR, EDGE_U, OUT_DL, OOB,    OOB,    OOB,
    OOB,    INN_UR, CRNR_DR,FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OUT_DR, CRNR_UR,FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const Map room0(12, 10, Direction::DOWN | Direction::UP, map0);

// int dummy_size_x = 9;
// int dummy_size_y = 6;
// uint8_t dummy_map[] = {
//     OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,
//     OOB,    EDGE_D, EDGE_D, EDGE_D, CRNR_DR,FLOOR1, CRNR_DL,EDGE_D, OOB,
//     EDGE_R, FLOOR3, FLOOR0, FLOOR2, FLOOR0, FLOOR3, FLOOR3, FLOOR2, EDGE_L,
//     EDGE_R, FLOOR1, CRNR_UL,EDGE_U, CRNR_UR,FLOOR0, CRNR_UL,EDGE_U, OOB,
//     EDGE_R, FLOOR2, EDGE_L, OOB,    EDGE_R, FLOOR2, EDGE_L, OOB,    OOB,
//     EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    EDGE_U, OOB,    OOB,    OOB
// };
