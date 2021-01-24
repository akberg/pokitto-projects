#pragma once
#include <vector>

#include "Map.h"

class Scene {
private:
    void linkSceneAck(Direction d, Scene* s); 
public:
    const Room& map;
    // Controls effect
    // Alternate palette
    Scene* links[4];    // Must be pointer, array of references not allowed
    uint8_t linksFlag;

    Scene(const Room& map);

    uint8_t getWidth() { return this->map.width; }
    uint8_t getHeight() { return this->map.height; }
    const uint8_t* getTilemap() { return this->map.tilemap; }

    // Link scene to another in the given direction,
    // other Scene links back
    void linkScene(Direction d, Scene* s);

    pos_t changeScene(Direction);
};

Scene& build_world(int seed, std::vector<Scene> &game);
