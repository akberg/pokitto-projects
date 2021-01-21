#include "Pokitto.h"
#include "Tilemap.hpp"
//#include "POKITTO_CORE/PokittoTimer.h"
#include "assets/StationTiles.h"

#include "Data.h"

//Pokitto::Core mygame;

//#define WIDTH 110
//#define HEIGHT 88
using PC = Pokitto::Core;
using PD = Pokitto::Display;

// const uint16_t worldWidth = 9 * 16;        // 16 tiles of 16 pixels
// const uint16_t worldHeight = 6 * 16;        // 16 tiles of 16 pixels

const uint16_t worldWidth = 16 * 16;        // 16 tiles of 16 pixels
const uint16_t worldHeight = 16 * 16;        // 16 tiles of 16 pixels

enum TileType {
    
	Water = 0,
	Green = 1,
	Tree = 2,
	Grass = 3,
	
};



int16_t x = 48;
int16_t y = 48;

void calculateViewPortPosition(int16_t &xViewPort, int16_t &yViewPort) {
    if (x < PD::width / 2) {
        xViewPort = 0;
    }
    else if (x > worldWidth - PD::width / 2) {
        xViewPort = PD::width - worldWidth;
    }
    else {
        xViewPort = PD::width / 2 - x;
    }
    if (y < PD::height / 2) {
        yViewPort = 0;
    }
    else if (y > worldHeight - PD::height / 2) {
        yViewPort = PD::height - worldHeight;
    }
    else {
        yViewPort = PD::height / 2 - y;
    }    
}

void calculatePlayerPosition(int16_t &xPlayer, int16_t &yPlayer) {
    if (x < PD::width / 2) {
        xPlayer = x;
    }
    else if (x > worldWidth - PD::width / 2) {
        xPlayer = x - (worldWidth - PD::width);
    }
    else {        
        xPlayer = PD::width / 2;
    }    
    if (y < PD::height / 2) {       
        yPlayer = y;
    }
    else if (y > worldHeight - PD::height / 2) {
        yPlayer = y - (worldHeight - PD::height);
    }
    else {
    
        yPlayer = PD::height / 2;
    }
}


int main() {
    Tilemap tilemap;
    PC::begin();
    PD::load565Palette(StationTiles_pal);
    //PD::loadRGBPalette(palettePico);
    PD::persistence = true;
    PD::invisiblecolor = 12;

    // tilemap.set(16, 16, Data::mapPixels);
    // tilemap.setTile(TileType::Green, 16, 16, Data::green16);
    // tilemap.setTile(TileType::Tree, 16, 16, Data::tree16);
    // tilemap.setTile(TileType::Grass, 16, 16, Data::grass16);
    // tilemap.setTile(TileType::Water, 16, 16, Data::water16);    
    //mygame.begin();
    //mygame.display.load565Palette(stationtiles_pal);
    //mygame.display.bgcolor = 0xFF;
    tilemap.set(9, 6, dummy_map);
    //tilemap.set(16, 16, all_floor);
    for (uint8_t i = FLOOR0; i != ERR; i++) {
        tilemap.setTile(i, 16, 16, StationTiles[i]+2);
    }
    // tilemap.setTile(StationTile::FLOOR0, 16, 16, StationTiles[FLOOR0]+2);
    // tilemap.setTile(StationTile::FLOOR1, 16, 16, StationTiles[FLOOR1]+2);
    // tilemap.setTile(StationTile::FLOOR2, 16, 16, StationTiles[FLOOR2]+2);
    // tilemap.setTile(StationTile::FLOOR3, 16, 16, StationTiles[FLOOR3]+2);
    // tilemap.setTile(StationTile::OOB, 16, 16, StationTiles[OOB]+2);
    // tilemap.setTile(StationTile::CRNR_UR, 16, 16, StationTiles[CRNR_UR]+2);
    // tilemap.setTile(StationTile::CRNR_DR, 16, 16, StationTiles[CRNR_DR]+2);
    // tilemap.setTile(StationTile::CRNR_UL, 16, 16, StationTiles[CRNR_UL]+2);
    // tilemap.setTile(StationTile::CRNR_DL, 16, 16, StationTiles[CRNR_DL]+2);
    // tilemap.setTile(StationTile::EDGE_U, 16, 16, StationTiles[EDGE_U]+2);
    // tilemap.setTile(StationTile::EDGE_D, 16, 16, StationTiles[EDGE_D]+2);
    // tilemap.setTile(StationTile::EDGE_L, 16, 16, StationTiles[EDGE_L]+2);
    // tilemap.setTile(StationTile::EDGE_R, 16, 16, StationTiles[EDGE_R]+2);
    while (PC::isRunning()) {
        if (!PC::update()) { continue; }

        //PD::drawBitmap(0, 0, edge_d);
        //PD::setCursor(16, 0);
        //PD::print("hello world");

        PC::buttons.pollButtons();        

        int16_t oldX = x;
        int16_t oldY = y;

        if (PC::buttons.pressed(BTN_LEFT)  || PC::buttons.repeat(BTN_LEFT, 1))    { x = x - 1; }
        if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))   { x = x + 1; }
        if (PC::buttons.pressed(BTN_UP)    || PC::buttons.repeat(BTN_UP, 1))      { y = y - 1; }
        if (PC::buttons.pressed(BTN_DOWN)  || PC::buttons.repeat(BTN_DOWN, 1))    { y = y + 1; }

        // // Check the map tile under the girl.
        // uint8_t tileId = tilemap.GetTileId(x + 6, y + 7, 16);

        // // If the tile is not grass, do not move.
        // // if (tileId != TileType::Green) {
        // //     x = oldX;
        // //     y = oldY;
        // // }

        // Check for out of bounds.
        if (x < 0)                          x = 0;
        if (x > worldWidth - 12)            x = worldWidth;
        if (y < 0)                          y = 0;
        if (y > worldHeight - 15)           y = worldHeight;
        
        int16_t xViewPort;
        int16_t yViewPort;

        calculateViewPortPosition(xViewPort, yViewPort);
        tilemap.draw(xViewPort, yViewPort);

        // int16_t xPlayer;
        // int16_t yPlayer;

        // calculatePlayerPosition(xPlayer, yPlayer);
        // PD::drawBitmapData(xPlayer, yPlayer, 12, 15, Data::girl12x15Pixels);
    }

    return 0;
}