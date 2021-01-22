#include "Pokitto.h"
#include "Tilemap.hpp"
//#include "POKITTO_CORE/PokittoTimer.h"
#include "assets/StationTiles.h"
//#include "assets/Map.h"

#include "Data.h" // example project

using PC = Pokitto::Core;
using PD = Pokitto::Display;

uint16_t worldWidth = 12 * PROJ_TILE_W;        // 16 tiles of 16 pixels
uint16_t worldHeight = 10 * PROJ_TILE_H;        // 16 tiles of 16 pixels

// const uint16_t worldWidth = 16 * 16;        // 16 tiles of 16 pixels
// const uint16_t worldHeight = 16 * 16;        // 16 tiles of 16 pixels

// enum TileType {
// 	Water = 0,
// 	Green = 1,
// 	Tree = 2,
// 	Grass = 3,
// };

int16_t x = 3*PROJ_TILE_W;
int16_t y = 9*PROJ_TILE_H;

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
    PD::persistence = true;
    PD::invisiblecolor = 6;

    //PD::loadRGBPalette(palettePico);
    // tilemap.set(16, 16, Data::mapPixels);
    // tilemap.setTile(TileType::Green, 16, 16, Data::green16);
    // tilemap.setTile(TileType::Tree, 16, 16, Data::tree16);
    // tilemap.setTile(TileType::Grass, 16, 16, Data::grass16);
    // tilemap.setTile(TileType::Water, 16, 16, Data::water16);    
    //mygame.begin();
    //mygame.display.load565Palette(stationtiles_pal);
    //mygame.display.bgcolor = 0xFF;
    // Map scene = room0;
    // worldWidth = 16 * 12;
    // worldHeight = 16 * 10;
    tilemap.set(12, 10, dummy_map);
    for (uint8_t i = FLOOR0; i != ERR; i++) {
        tilemap.setTile(i, 16, 16, StationTiles[i]+2);
    }
    while (PC::isRunning()) {
        if (!PC::update()) { continue; }

        PC::buttons.pollButtons();        

        int16_t oldX = x;
        int16_t oldY = y;

        if (PC::buttons.pressed(BTN_LEFT)  || PC::buttons.repeat(BTN_LEFT, 5))    { x = x - 16; }
        if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 5))   { x = x + 16; }
        if (PC::buttons.pressed(BTN_UP)    || PC::buttons.repeat(BTN_UP, 5))      { y = y - 16; }
        if (PC::buttons.pressed(BTN_DOWN)  || PC::buttons.repeat(BTN_DOWN, 5))    { y = y + 16; }

        // Check the map tile under the player.
        uint8_t tileId = tilemap.GetTileId(x + 6, y + 7, 16);

        // If the tile is not floor, do not move.
        if (tileId != StationTile::FLOOR0) {
            x = oldX;
            y = oldY;
        }

        // Check for out of bounds.
        if (x < 0)                          x = 0;
        if (x > worldWidth - 12)            x = worldWidth;
        if (y < 0)                          y = 0;
        if (y > worldHeight - 15)           y = worldHeight;
        
        int16_t xViewPort;
        int16_t yViewPort;

        calculateViewPortPosition(xViewPort, yViewPort);
        tilemap.draw(xViewPort, yViewPort);
        PD::color = 7;
        PD::bgcolor = PD::invisiblecolor;
        PD::fillRectangle(0, 0, 110, 16); // Draw 
        PD::color = 3;
        PD::setCursor(32, 0);
        PD::print("1:59");

        int16_t xPlayer;
        int16_t yPlayer;

        calculatePlayerPosition(xPlayer, yPlayer);
        PD::drawBitmapData(xPlayer, yPlayer, 16, 16, StationTiles[PLR0]+2);
    }

    return 0;
}

