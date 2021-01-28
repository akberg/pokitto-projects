#pragma once
#include <stdint.h>
#include <vector>

#include "StationTiles.hpp"

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

//---map control room---- start point
//..........
//....####..
//....####..
//########..
//....####..
//....####..
//..........
const uint8_t map_controlroom[] = {
    OOB,    OOB,    OOB,    OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D, OUT_DL, OOB,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,
    EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, FLOOR0, FLOOR0, CONS_R, EDGE_L, OOB,
    FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, CONS_R, EDGE_L, OOB,
    EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, FLOOR0, FLOOR0, CONS_R, EDGE_L, OOB,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, CONS_D, FLOOR0, FLOOR0, EDGE_L, OOB,
    OOB,    OOB,    OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U, EDGE_U, OUT_UL, OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_controlroom[] = {0, 0, 0, 3};

const Room room_controlroom(10, 8, (pos_t){6, 3}, entrances_controlroom, map_controlroom);

// --- map pod room --- finish point
//............
//.#########..
//.#########..
//.....#......
//.....#......
//....###.....
//....###.....
//############
//.....#......
//.....#......
const uint8_t map_podroom[] = {
    OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, OUT_DL, OOB,
    EDGE_R, CONS_L, FLOOR0, POD,    FLOOR0, POD,    FLOOR0, POD,    FLOOR0, CONS_R, EDGE_L, OOB,
    EDGE_R, CONS_L, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, CONS_R, EDGE_L, OOB,
    OUT_UR, EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, INN_UL, EDGE_U, EDGE_U, EDGE_U, OUT_UL, OOB,
    OOB,    OOB,    OOB,    OUT_DR, INN_DR, FLOOR0, INN_DL, OUT_DL, OOB,    OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,
    EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, FLOOR0, CONS_R, INN_DL, EDGE_D, EDGE_D, EDGE_D, EDGE_D,
    FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    EDGE_U, EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, INN_UL, EDGE_U, EDGE_U, EDGE_U, EDGE_U, EDGE_U,
    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_podroom[] = {0, 7, 5, 7 };
const Room room_podroom(12, 10, entrances_podroom, map_podroom);

//---map 0----
//.......#....
//.......#....
//.......#....
//...#######..
//...#...#....
//...#........
//...#........
//..##........
//...#........
const uint8_t map0[] = {
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    OUT_DR, EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, INN_DL, EDGE_D, OUT_DL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, INN_UL, EDGE_U, INN_UR, FLOOR0, INN_UL, EDGE_U, OUT_UL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OUT_UR, EDGE_U, OUT_UL, OOB,    OOB,    OOB,
    OOB,    OUT_DR, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OUT_UR, INN_UR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_room0[] = {7, 0, 3, 0};
const Room room0(12, 10, entrances_room0, map0);

//---map 1----
//.........#....
//.........#....
//..########....
//..#......#....
//..#......#....
//..#..#####....
//..#..#...#####
//..#..#........
//..#..#........
//..#..#####....
//.........#....
//.........#....
const uint8_t map1[] = {
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, INN_UL, EDGE_U, EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, EDGE_L, OUT_DR, EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, INN_DL, EDGE_D, EDGE_D, EDGE_D,
    OOB,    EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, INN_UL, EDGE_U, INN_UR, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    OOB,    EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L, OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U, EDGE_U, EDGE_U,
    OOB,    EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, INN_DL, EDGE_D, EDGE_D, EDGE_D, OUT_DL, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OUT_UR, EDGE_U, OUT_UL, OUT_UR, EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
};
const uint8_t entrances_room1[] = {9, 6, 9, 0};
const Room room1(14, 12, entrances_room1, map1);

//--- map2 ----
//........
//........
//########
//...#....
//...#....
//...#....
const uint8_t map2[] = {
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D,
    FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    EDGE_U, EDGE_U, INN_UR, FLOOR0, INN_UL, EDGE_U, EDGE_U, EDGE_U,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
};
const uint8_t entrances_room2[] = {0, 2, 3, 2};
const Room room2(8, 6, entrances_room2, map2);

// --- map 3 ---TODO: too small
//...#....
//...###..
//...#....
//...#....
//...#####
//........
const uint8_t map3[] = {
    OOB,    OOB,    EDGE_R, FLOOR0, INN_DL, EDGE_D, OUT_DL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, INN_UL, EDGE_U, OUT_UL, OOB,
    OOB,    OOB,    EDGE_R, FLOOR0, INN_DL, EDGE_D, EDGE_D, EDGE_D,
    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    OOB,    OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U, EDGE_U, EDGE_U,
};
const uint8_t entrances_room3[] = {3, 4, 0, 0};
const Room room3(8, 6, entrances_room3, map3);

// -- map 4 ---
//................
//................
//.....#..........
//#########.......
//..#..#..#..#####
//..#..#..#..#..#.
//..####..#..#..#.
//........#..#..#.
//........#..#....
//....#...####....
//....#####.......
//........#.......
const uint8_t map4[] = {
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OUT_DR, EDGE_D, OUT_DL, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    EDGE_D, EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, INN_DL, EDGE_D, EDGE_D, OUT_DL, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D,
    EDGE_U, INN_UR, FLOOR0, INN_UL, INN_UR, FLOOR0, INN_UL, INN_UR, FLOOR0, EDGE_L, EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    OOB,    EDGE_R, FLOOR0, INN_DL, INN_DR, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, INN_UL, INN_UR, FLOOR0, INN_UL,
    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L,
    OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U, EDGE_U, OUT_UL, EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L, EDGE_R, FLOOR0, EDGE_L,
    OOB,    OOB,    OOB,    OUT_DR, EDGE_D, OUT_DL, OOB,    EDGE_R, FLOOR0, INN_DL, INN_DR, FLOOR0, EDGE_L, OUT_UR, EDGE_U, OUT_UL,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, INN_DL, EDGE_D, INN_DR, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, INN_UL, EDGE_U, EDGE_U, OUT_UL, OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U, INN_UR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_room4[] = {0, 4, 8, 3};
const Room room4(16, 12, entrances_room4, map4);

// --- map 5 ---
//........
//........
//........
//....####
//....##..
//....#...
const uint8_t map5[] = { // TODO: too small
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D,  
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, CONS_R, INN_UL, EDGE_U,
    OOB,    OOB,    OOB,    EDGE_R, FLOOR0, INN_UL, OUT_UL, OOB,
};
const uint8_t entrances_room5[] = {0, 3, 4, 0};
const Room room5(8, 6, entrances_room5, map5);

// --- map 6 ---
//...#....
//.#####..
//##...###
//........
//........
//........
const uint8_t map6[] = {
    OUT_DR, EDGE_D, INN_DR, FLOOR0, INN_DL, EDGE_D, OUT_DL, OOB,
    INN_DR, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, INN_DL, EDGE_D,
    FLOOR0, FLOOR0, INN_UL, EDGE_U, INN_UR, FLOOR0, FLOOR0, FLOOR0,
    EDGE_U, EDGE_U, OUT_UL, OOB,    OUT_UR, EDGE_U, EDGE_U, EDGE_U,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_room6[] = {3, 2, 0, 2};
const Room room6(8, 6, entrances_room6, map6);

// --- map 7 ---
//..........
//..#######.
//###..#..#.
//.....#....
//.....#....
//.#####....
//..#.......
//..#.......

const uint8_t map7[] = {
    OOB,    OUT_DR, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, EDGE_D, OOB,
    EDGE_D, INN_DR, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L,
    FLOOR0, FLOOR0, FLOOR0, INN_UL, INN_UR, FLOOR0, INN_UL, INN_UR, FLOOR0, EDGE_L,
    EDGE_U, EDGE_U, EDGE_U, OUT_UL, EDGE_R, FLOOR0, EDGE_L, OUT_UR, EDGE_U, OUT_UL,
    OUT_DR, EDGE_D, EDGE_D, EDGE_D, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    EDGE_R, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OUT_UR, INN_UR, FLOOR0, INN_UL, EDGE_U, EDGE_U, OUT_UL, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, EDGE_L, OOB,    OOB,    OOB,    OOB,    OOB,    OOB,
};
const uint8_t entrances_room7[] = {0, 0, 2, 2};
const Room room7(10, 8, entrances_room7, map7);

// --- room 8 ---
//.....#....
//...###....
//..#..#....
//..#..#....
//######....
//..........
const uint8_t map8[] = {
    OOB,    OOB,    OUT_DR, EDGE_D, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    OUT_DR, INN_DR, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    OOB,    EDGE_R, FLOOR0, INN_UL, INN_UR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    EDGE_D, INN_DR, FLOOR0, INN_DL, INN_DR, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, FLOOR0, EDGE_L, OOB,    OOB,    OOB,
    EDGE_U, EDGE_U, EDGE_U, EDGE_U, EDGE_U, EDGE_U, OUT_UL, OOB,    OOB,    OOB,
};
const uint8_t entrances_room8[] = {5, 0, 0, 4};
const Room room8(10, 6, entrances_room8, map8);