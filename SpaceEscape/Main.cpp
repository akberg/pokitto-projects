#include "Pokitto.h"
#include "Tilemap.hpp"
#include "assets/StationTiles.h"
#include "assets/TitleScreen.h"
#include "assets/StorySequence.h"
#include "assets/Scene.h"

#include <unordered_set>
#include <cstdlib>


enum GameResult { WIN, LOSS };

using PC = Pokitto::Core;
using PD = Pokitto::Display;

uint16_t worldWidth = 12 * PROJ_TILE_W;        // 16 tiles of 16 pixels
uint16_t worldHeight = 10 * PROJ_TILE_H;        // 16 tiles of 16 pixels

// Player x render position
int16_t x = 6*PROJ_TILE_W;
// Player y render position
int16_t y = 3*PROJ_TILE_H;

/**
 * Calculate viewport position to keep player in focus
 * Extern variables: x, y, worldWidth, worldHeight
 * */
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

/**
 * Calculate player's position on screen
 * Extern variables: x, y, worldWidth, worldHeight
 * */
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

/**
 * Format time from ms to mm:ss format
 * */
void formatTime(char* buffer, int time)
{
    time /= 1000;
    int sec = time % 60;
    int min = (time - sec) / 60;
    sprintf(buffer, "%02d:%02d", min, sec);
}

int dx = 0;// not in use
int dy = 0;

GameResult game() 
{
    GameResult result = GameResult::WIN;
    /**
     * Display setup 
     * */
    PD::setFont(fontTight);
    Tilemap tilemap; // FIXME: Tilemap not drawing on the edges, leaves artifacts
    
    PD::load565Palette(StationTiles_pal);
    //PD::persistence = true;
    PD::invisiblecolor = STINVISIBLE;


    for (uint8_t i = FLOOR0; i != ERR; i++) {
        tilemap.setTile(i, 16, 16, StationTiles[i]+2);
    }

    bool dialogVisible = false;
    char* dialogString;
    
    // *build and load game
    // TODO: extract, extend and randomise 
    // std::vector<Scene*> world;
    // Scene start(room_controlroom);
    // Scene podroom(room_podroom);
    // Scene scene0(room0);
    // Scene scene1(room1);
    // world.push_back(&start);
    // world.push_back(&podroom);
    // world.push_back(&scene0);
    // world.push_back(&scene1);
    
    // start.linkScene(Direction::LEFT, &scene1);
    // scene1.linkScene(Direction::DOWN, &scene0);
    // scene1.linkScene(Direction::UP, &podroom);

    std::vector<Scene*> world = build_world(randint(2));
    Scene* scene = world[0];
    x = scene->map.spawn_fallback.x * TILE_SIZE;
    y = scene->map.spawn_fallback.y * TILE_SIZE;
    // *build and load game


    /**
     * Set boundaries to scene values 
     * */
    worldWidth = scene->getWidth() * PROJ_TILE_W;
    worldHeight = scene->getHeight() * PROJ_TILE_H;
    tilemap.set(scene->getWidth(), scene->getHeight(), scene->getTilemap());


    /**
     * Set up timer to 2 min
     * */
    int t_meltdown = (int)PC::getTime() + 2 * 60 * 1000;
    char timestring[6];

    
    while (PC::isRunning()) {
        if (!PC::update()) { continue; }

        //PC::buttons.pollButtons();        

        int16_t oldX = x;
        int16_t oldY = y;

        if (PC::buttons.repeat(scene->controlMapping[BTN_LEFT], 5)) { 
            dialogVisible = false;
            x = x - 16; 
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_RIGHT], 5)) { 
            dialogVisible = false;
            x = x + 16; 
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_UP], 5)) { 
            dialogVisible = false;
            y = y - 16; 
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_DOWN], 5)) { 
            dialogVisible = false;
            y = y + 16; 
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_A], 5)) { 
            dialogVisible = false;
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_B], 5)) { 
            dialogVisible = false;
        }
        if (PC::buttons.repeat(scene->controlMapping[BTN_C], 5)) { 
            dialogVisible = false;
        }


        /**
         * Change scene
         * */
        bool changeScene = false;
        Direction d;
        if (x < 0 && scene->linksFlag & 1 << Direction::LEFT) {
            changeScene = true;
            d = Direction::LEFT;
        }
        else if (x > worldWidth-TILE_SIZE && scene->linksFlag & 1 << Direction::RIGHT) {
            changeScene = true;
            d = Direction::RIGHT;
        }
        else if (y < 0 && scene->linksFlag & 1 << Direction::UP) {
            changeScene = true;
            d = Direction::UP;
        }
        else if (y > worldHeight-TILE_SIZE && scene->linksFlag & 1 << Direction::DOWN) {
            changeScene = true;
            d = Direction::DOWN;
        }
        else if (x < 0 || x > worldWidth || y < 0 || y > worldHeight) {
            // No link in this direction: "door is locked"
            dialogVisible = true;
            switch (rand() % 3) {
            case 0:
                dialogString = (char*)"This door doesn't seem to\n go anywhere.         ";
                break;
            case 1:
                dialogString = (char*)"That door is locked, \nthere must be another way.";
                break;
            case 2:
                dialogString = (char*)"This one's jammed...                             ";
            }
            x = oldX;
            y = oldY;
        }
        else {
            // Check the map tile under the player, if no change of scene
            uint8_t tileId = tilemap.GetTileId(x + 6, y + 7, 16);
            // If the tile is not floor, do not move.
            if (WALKABLES.find((StationTile)tileId) == WALKABLES.end()/*tileId != StationTile::FLOOR0*/) {
                x = oldX;
                y = oldY;
            }
            if (tileId == StationTile::POD) { goto game_cleanup; }
        }
        if (changeScene) {
            pos_t newPos = scene->changeScene(d); // Get spawn position in next scene
            x = newPos.x;
            y = newPos.y;
            scene = scene->links[d]; // Change scene

            // Update tilemap
            worldWidth = scene->getWidth() * PROJ_TILE_W;
            worldHeight = scene->getHeight() * PROJ_TILE_H;
            tilemap.set(scene->getWidth(), scene->getHeight(), scene->getTilemap());
        }
        

        /**Draw tilemap */
        int16_t xViewPort;
        int16_t yViewPort;

        PD::bgcolor = 3;
        calculateViewPortPosition(xViewPort, yViewPort);
        tilemap.draw(xViewPort, yViewPort);


        /**Timer */
        PD::bgcolor = PD::invisiblecolor;
        PD::color = StationTilesColor::STRED;
        PD::setCursor(42, 2);
        if ((int)(t_meltdown - PC::getTime()) < 0) { 
            // Out of time
            result = GameResult::LOSS;
            goto game_cleanup; 
        } 
        formatTime(timestring, t_meltdown - PC::getTime());
        PD::print(timestring);

        // !!! DEBUG !!!
        // if (PC::buttons.repeat(BTN_A, 5)) { return GameResult::WIN; }
        // if (PC::buttons.repeat(BTN_B, 5)) { return GameResult::LOSS; }
        // !!! DEBUG !!!


        /**
         * Player
         * */
        int16_t xPlayer;
        int16_t yPlayer;

        calculatePlayerPosition(xPlayer, yPlayer);
        PD::drawBitmapData(xPlayer, yPlayer, 16, 16, StationTiles[PFRONT_STILL]+2);


        /**
         * Dialog
         * */
        if (dialogVisible) {
            PD::color = 5;
            PD::fillRectangle(0, 0, PD::width, 24);
            PD::color = STBLACK;
            PD::drawRectangle(0, 0, PD::width, 24);
            PD::setCursor(2, 2);
            PD::color = StationTilesColor::STBLACK;
            PD::bgcolor = PD::invisiblecolor;
            PD::print(dialogString);
        }
    }

game_cleanup:
    for (Scene* pt : world) {
        delete pt;
    }

    return result;
}


void stateTitleScreen()
{
    // display title screen and wait for 'A' button press
    PD::load565Palette(TitleScreen_pal);
    PD::invisiblecolor = 16;

    while (PC::isRunning()) {
        if (PC::update()) {
            PD::drawBitmap(0, 0, TitleScreen);
            if (PC::buttons.repeat(BTN_A, 5)) {
                return;
            }
        }
    }
}


void stateIntro()
{
    int step = 0; // Story step
    PD::load565Palette(StorySequence_pal);
    PD::invisiblecolor = StorySequenceInvisibleColor;
    PD::color = StorySequenceTextColor;
    PD::bgcolor = StorySequenceInvisibleColor;

    while (PC::isRunning()) {
        if (!PC::update()) { continue; }
        if (PC::buttons.repeat(BTN_A, 5)) {
            step++;
        }
        if (step >= StorySequenceDialogLength || PC::buttons.repeat(BTN_C, 5)) {
            return;
        }

        /**Draw background */
        PD::drawBitmap(0, 0, StorySequence[(int)(step >= StorySequenceScene1)]);
        /**Draw text background */
        PD::drawBitmap(0, 0, StorySequence[2]);
        /**Print dalog text */
        PD::setCursor(2, 2);
        PD::print(StorySequenceDialog[step]);
    }
}


void stateEndGame(GameResult result)
{
    PD::load565Palette(StorySequence_pal);
    PD::invisiblecolor = StorySequenceInvisibleColor;
    PD::color = StorySequenceTextColor;
    PD::bgcolor = StorySequenceInvisibleColor;

    while (PC::isRunning()) {
        if (PC::update()) {
            PD::drawBitmap(0, 0, StorySequence[3 + (uint8_t)result]);
            if (PC::buttons.repeat(BTN_A, 5)) {
                return;
            }
        }
    }
}


/**
 * State machine, between game, title screen, and win/loss screen
 * */
int main()
{
    std::srand(PC::getTime()); // Seed random

    PC::begin();
    PD::setFont(fontTight);

    while (true) {
        stateTitleScreen();
        stateIntro();
        GameResult result = game();
        stateEndGame(result);
    }
}
