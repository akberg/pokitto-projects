#pragma once
#include <vector>

#include "Map.h"

class Scene {
private:
    void linkSceneAck(Direction d, Scene* s); 
public:
    const Room& map;
    // Controls effect
    uint16_t controlMapping[7];
    Scene* links[4];    // Must be pointer, array of references not allowed
    uint8_t linksFlag;

    Scene(const Room& map);
    Scene(const Room& map, const uint16_t* controlMapping);

    uint8_t getWidth() { return this->map.width; }
    uint8_t getHeight() { return this->map.height; }
    const uint8_t* getTilemap() { return this->map.tilemap; }

    // Link scene to another in the given direction,
    // other Scene links back
    void linkScene(Direction d, Scene* s);

    pos_t changeScene(Direction);
};

std::vector<Scene*> build_world(int seed);

const uint8_t num_control_mappings = 6;
const uint16_t control_mappings[][7] = {
    {5, 2, 3, 1, 0, 4, 6},
    {6, 5, 4, 3, 2, 1, 0},
    {1, 3, 5, 0, 2, 4, 6},
    {0, 2, 4, 6, 1, 3, 5},
    {4, 6, 3, 1, 5, 0, 2},
    {3, 1, 0, 5, 4, 2, 3}
};

