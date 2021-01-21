#pragma once
#include <stdint.h>

#include "StationTiles.h"

/**
 * Map to be used in combination with effects and pointers to other rooms to make 
 * a Room. All maps are static and compiled
 * */
class Map {
private:

public:
    const uint8_t size_x;
    const uint8_t size_y;

};

int dummy_size_x = 9;
int dummy_size_y = 6;
uint8_t dummy_map[] = {
    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,
    OOB,    EDGE_D, EDGE_D, EDGE_D, CRNR_DR,FLOOR1, CRNR_DL,EDGE_D, OOB,
    EDGE_R, FLOOR3, FLOOR0, FLOOR2, FLOOR0, FLOOR3, FLOOR3, FLOOR2, EDGE_L,
    EDGE_R, FLOOR1, CRNR_UL,EDGE_U, CRNR_UR,FLOOR0, CRNR_UL,EDGE_U, OOB,
    EDGE_R, FLOOR2, EDGE_L, OOB,    EDGE_R, FLOOR2, EDGE_L, OOB,    OOB,
    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    EDGE_U, OOB,    OOB,    OOB
};
// uint8_t dummy_map[] = {

//     0x44,   0x44,   0xc0,   0xa4,   0x44,
//     0x4b,   0xdd,   0x81,   0x7b,   0x44,
//     0xc3,   0x02,   0x03,   0x32,   0xa4,
//     0xc1,   0x69,   0x50,   0x69,   0x44,
//     0xc2,   0xa4,   0xc2,   0xa4,   0x44,
//     0xc0,   0xa4,   0x4a,   0x44,   0x44
// };