#include "Scene.h"
#include <unordered_set>


Scene::Scene(const Room& map) : map(map) {
    this->linksFlag = 0;
    for (int i = 0; i < 7; i++)
        this->controlMapping[i] = i;   
}

Scene::Scene(const Room& map, const uint16_t* controlMapping) : Scene(map) {
    for (int i = 0; i < 7; i++)
        this->controlMapping[i] = controlMapping[i];
}

void Scene::linkScene(Direction d, Scene* s) {
    this->links[d] = s;
    this->linksFlag |= 1<<d;
    s->linkSceneAck(dir_opposit(d), this);
}
void Scene::linkSceneAck(Direction d, Scene* s) {
    this->links[d] = s;
    this->linksFlag |= 1<<d;
}

pos_t Scene::changeScene(Direction d) {
    return links[d]->map.get_entrance(dir_opposit(d));
}

std::vector<Scene*> build_world(int seed) {
    std::vector<Scene*> world;
    Scene* start = new Scene(room_controlroom);
    world.push_back(start);
    switch (seed)
    {
    case 0: {
        Scene* podroom = new Scene(room_podroom);
        Scene* scene0 = new Scene(room0, control_mappings[0]);
        Scene* scene1 = new Scene(room1, control_mappings[4]);
        world.push_back(podroom);
        world.push_back(scene0);
        world.push_back(scene1);
        
        start->linkScene(Direction::LEFT, scene1);
        scene1->linkScene(Direction::DOWN, scene0);
        scene1->linkScene(Direction::UP, podroom);
        break;
    }
    default: 
        // Use seed to randomly generate world
        break;

    }
    return world;
}