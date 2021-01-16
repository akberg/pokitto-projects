#include "Pokitto.h"
#include "pokitto_icon.h"

Pokitto::Core mygame;

int main() {
    mygame.begin();
    mygame.display.load565Palette(pokitto_icon_pal);
    mygame.display.bgcolor = 1;
    int x = 0, y = 0;
    while (mygame.isRunning()) {
        if (mygame.update()) {
            mygame.display.setColor(1);

            if (mygame.buttons.upBtn() && y > 0) y --;
            if (mygame.buttons.downBtn() && y < mygame.display.height) y++;
            if (mygame.buttons.leftBtn() && x > 0) x--;
            if (mygame.buttons.rightBtn() && x < mygame.display.width) x++;

            mygame.display.drawBitmap(x, y, pokitto_icon);
        }
    }

    return 0;
}