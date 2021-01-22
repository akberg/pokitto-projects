#pragma once

#include "Map.h"

class Scene {
public:
    Map* map;
    // Controls effect
    // Alternate palette

    uint8_t getWidth() { return this->map->width; }
    uint8_t getHeight() { return this->map->height; }

}