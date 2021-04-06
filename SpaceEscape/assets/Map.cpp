#include "Map.hpp"

extern const std::unordered_set<StationTile> WALKABLES;

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
        return (pos_t){entrances[d], 0 };
        break;
    case Direction::DOWN:
        return (pos_t){entrances[d], this->height - 1 };
        break;
    case Direction::LEFT:
        return (pos_t){0, entrances[d]};
        break;
    case Direction::RIGHT:
        return (pos_t){this->width - 1, entrances[d]};
        break;
    default:
        return {0, 0};
        break;
    }
}

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

volatile const Room room_controlroom(10, 8, (pos_t){6, 3}, entrances_controlroom, map_controlroom);

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
volatile const Room room_podroom(12, 10, entrances_podroom, map_podroom);

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
volatile const Room room0(12, 10, entrances_room0, map0);

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
volatile const Room room1(14, 12, entrances_room1, map1);

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
volatile const Room room2(8, 6, entrances_room2, map2);

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
volatile const Room room3(8, 6, entrances_room3, map3);

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
volatile const Room room4(16, 12, entrances_room4, map4);

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
volatile const Room room5(8, 6, entrances_room5, map5);

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
volatile const Room room6(8, 6, entrances_room6, map6);

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
volatile const Room room7(10, 8, entrances_room7, map7);

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
volatile const Room room8(10, 6, entrances_room8, map8);
