#include "Scene.h"
#include <unordered_set>


Scene::Scene(const Room& map) : map(map) {
    this->linksFlag = 0;
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

Scene& build_world(int seed, std::vector<Scene> &world) {
    switch (seed)
    {
    case 0: {
        Scene start(room_controlroom);
        Scene scene0(room0);
        Scene scene1(room1);
        world.push_back(start);
        world.push_back(scene0);
        world.push_back(scene1);
        
        start.linkScene(Direction::LEFT, &scene1);
        scene1.linkScene(Direction::DOWN, &scene0);
        scene1.linkScene(Direction::UP, &scene0);

        break;
    }
    default: 
        // Use seed to randomly generate world
        break;

    }
}