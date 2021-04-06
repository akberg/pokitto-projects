#pragma once
#include <stdint.h>
#include <unordered_set>

enum StationTile {
    FLOOR0 = 0, 
    CONS_R,
    CONS_L,
    CONS_D,
    POD,
    OOB, 
    INN_UR, 
    INN_UL, 
    INN_DL, 
    INN_DR, 
    EDGE_U, 
    EDGE_L, 
    EDGE_D, 
    EDGE_R,
    OUT_DR,
    OUT_DL,
    OUT_UL,
    OUT_UR,

    PFRONT_STILL,
    PFRONT_STEP0,
    PFRONT_STEP1,
    PLEFT_STILL,
    PLEFT_STEP0,
    PLEFT_STEP1,
    PBACK_STILL,
    PBACK_STEP0,
    PBACK_STEP1,
    ERR, // Delimiter
};

//extern const std::unordered_set<StationTile> WALKABLES;

#define ST_PALETTE_SIZE 11
enum StationTilesColor { STBLACK=3, STRED=8, STWHITE=0, STINVISIBLE=7 };

//extern const uint16_t StationTiles_pal[];
//extern const uint8_t StationTiles [][130];
//Sprite sheet:5x6
