#include "Pokitto.h"
//#include "POKITTO_CORE/PokittoTimer.h"
//#include "pokitto_icon.h"

Pokitto::Core mygame;

#define WIDTH 110
#define HEIGHT 88
#define PAD_H 4
#define SQSIZE 5    // 16x22

#define NX WIDTH / SQSIZE
#define NY (HEIGHT - PAD_H * 2) / SQSIZE

int x = 0;
int y = 0;
int counter = 0;
int running = 0;
int frame = 0;

char cells[NX][NY];

int main() {
    mygame.begin();
    //mygame.display.load565Palette(pokitto_icon_pal);
    mygame.display.bgcolor = 0;
    while (mygame.isRunning()) {
        counter = (counter+1) % 24;
        if (mygame.update()) {
            // Start stop simulation
            if (mygame.buttons.repeat(BTN_B, 10)) running = !running;

            if (!running) {
                // move cursor
                if (mygame.buttons.repeat(BTN_UP, 10) && y > 0) y --;
                if (mygame.buttons.repeat(BTN_DOWN, 10) && y+1 < NY) y++;
                if (mygame.buttons.repeat(BTN_LEFT, 10) && x > 0) x--;
                if (mygame.buttons.repeat(BTN_RIGHT, 10) && x+1 < NX) x++;
                // clear cells
                if (mygame.buttons.repeat(BTN_C, 10)) memset(cells, 0, NX * NY * sizeof(char));
                if (mygame.buttons.repeat(BTN_A, 10)) cells[x][y] = !cells[x][y];
            } else {
                if (counter > 12 && frame)
                    frame = 0;
                if (counter <= 12 && !frame) {
                    frame = 1;
                    // game of life logic
                    char trans[NX][NY];
                    memset(trans, 0, NX * NY * sizeof(char));
                    // Count neighbours
                    for (int i = 0; i < NX; i++) {
                        for (int j = 0; j < NY; j++) {
                            if (cells[i][j]) {
                                if (i>0) trans[i-1][j]++;
                                if (j>0) trans[i][j-1]++;
                                if (i>0 && j>0) trans[i-1][j-1]++;
                                if (i>0 && j+1<NY) trans[i-1][j+1]++;
                                if (i+1<NX && j>0) trans[i+1][j-1]++;
                                if (i+1<NX & j+1<NY) trans[i+1][j+1]++;
                                if (i+1<NX) trans[i+1][j]++;
                                if (j+1<NY) trans[i][j+1]++;
                            }
                        }
                    }
                    // Apply rules
                    for (int i = 0; i < NX; i++) {
                        for (int j = 0; j < NY; j++) {
                            if (cells[i][j]) {
                                if (trans[i][j] < 2 || trans[i][j] > 3) cells[i][j] = 0;
                            } else {
                                if (trans[i][j] == 3) cells[i][j] = 1;
                            }
                        }
                    }
                }
                
            }
            
            // draw grid
            for (int i = 0; i < NX; i++) {
                for (int j = 0; j < NY; j++) {
                    mygame.display.color = cells[i][j] ? 3 : 2;
                    mygame.display.fillRectangle(i * SQSIZE, j * SQSIZE + PAD_H, SQSIZE, SQSIZE);
                    mygame.display.color = 3;
                    mygame.display.drawRectangle(i * SQSIZE, j * SQSIZE + PAD_H, SQSIZE, SQSIZE);
                }
            }
            if (!running) {
                mygame.display.color = 0;
                if (counter > 12) {
                    mygame.display.fillRectangle(x * SQSIZE + 1, y * SQSIZE + PAD_H + 1, SQSIZE-1, SQSIZE-2);
                    mygame.display.color = 1;
                    mygame.display.drawRectangle(x * SQSIZE + 1, y * SQSIZE + PAD_H + 1, SQSIZE-2, SQSIZE-2);
                }
            }
            mygame.wait(50);
        }
    }

    return 0;
}