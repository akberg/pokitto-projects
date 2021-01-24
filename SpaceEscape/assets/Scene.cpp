#include "Scene.h"
#include <unordered_set>
#include <cstdlib>


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

// return a random, positive integer lower than lim
int randint(int lim) { return rand() % lim; }

std::vector<Scene*> build_world(int seed) {
    std::vector<Scene*> world;
    Scene* start = new Scene(room_controlroom);
    Scene* podroom = new Scene(room_podroom);
    world.push_back(start);
    world.push_back(podroom);

    int lim = ST_PALETTE_SIZE;

    switch (seed)
    {
    case 0: {
        // Simple example game
        Scene* scene0 = new Scene(room0, control_mappings[randint(lim)]);
        Scene* scene1 = new Scene(room1, control_mappings[randint(lim)]);
        world.push_back(scene0);
        world.push_back(scene1);
        
        start->linkScene(Direction::LEFT, scene1);
        scene1->linkScene(Direction::DOWN, scene0);
        scene1->linkScene(Direction::UP, podroom);
        break;
    }
    case 1: {
        // Hard coded game no 2
        Scene* scene0 = new Scene(room4);
        Scene* scene1 = new Scene(room0);
        Scene* scene2 = new Scene(room1);
        Scene* scene3 = new Scene(room5);
        Scene* scene4 = new Scene(room6);
        Scene* scene5 = new Scene(room3);
        Scene* scene6 = new Scene(room6);
        Scene* scene7 = new Scene(room5);
        Scene* scene8 = new Scene(room0);
        Scene* scene9 = new Scene(room2);
        Scene* scene10 = new Scene(room6);
        Scene* scene11 = new Scene(room8);
        Scene* scene12 = new Scene(room7);
        start->linkScene(Direction::LEFT, scene0);
        scene0->linkScene(Direction::DOWN, scene1);
        scene0->linkScene(Direction::LEFT, scene2);
        scene2->linkScene(Direction::UP, scene3);
        scene2->linkScene(Direction::DOWN, scene5);
        scene5->linkScene(Direction::RIGHT, scene4);
        scene6->linkScene(Direction::UP, scene1);
        scene6->linkScene(Direction::LEFT, scene7);
        scene6->linkScene(Direction::RIGHT, scene9);
        scene7->linkScene(Direction::DOWN, scene8);
        scene8->linkScene(Direction::DOWN, scene4);
        scene9->linkScene(Direction::RIGHT, scene10);
        scene10->linkScene(Direction::RIGHT, scene11);
        scene11->linkScene(Direction::UP, scene12);
        podroom->linkScene(Direction::DOWN, scene10);
        podroom->linkScene(Direction::RIGHT, scene12);
    }
    default: 
        // Use seed to randomly generate world
        break;

    }
    return world;
}