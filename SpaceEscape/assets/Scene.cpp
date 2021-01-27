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

    int lim = num_control_mappings;

    switch (seed)
    {
    case 0: {
        // Debug, minimal game without controls mapping
        Scene* scene0 = new Scene(room1);
        start->linkScene(Direction::LEFT, scene0);
        podroom->linkScene(Direction::DOWN, scene0);
        break;
    }
    case 1: {
        // Hard coded game no 1
        Scene* scene0 = new Scene(room4, control_mappings[randint(lim)]);
        Scene* scene1 = new Scene(room0, control_mappings[randint(lim)]);
        Scene* scene2 = new Scene(room1);
        Scene* scene3 = new Scene(room5, control_mappings[randint(lim)]);
        Scene* scene4 = new Scene(room6, control_mappings[randint(lim)]);
        Scene* scene5 = new Scene(room3, control_mappings[randint(lim)]);
        Scene* scene6 = new Scene(room6, control_mappings[randint(lim)]);
        Scene* scene7 = new Scene(room5, control_mappings[randint(lim)]);
        Scene* scene8 = new Scene(room0, control_mappings[randint(lim)]);
        Scene* scene9 = new Scene(room2, control_mappings[randint(lim)]);
        Scene* scene10 = new Scene(room6, control_mappings[randint(lim)]);
        Scene* scene11 = new Scene(room8);
        Scene* scene12 = new Scene(room7, control_mappings[randint(lim)]);
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
        break;
    }
    case 2: {
        // Hard coded game no 2
        Scene* scene0 = new Scene(room1, control_mappings[randint(lim)]);
        Scene* scene1 = new Scene(room4, control_mappings[randint(lim)]);
        Scene* scene2 = new Scene(room3);
        Scene* scene3 = new Scene(room5, control_mappings[randint(lim)]);
        Scene* scene4 = new Scene(room7, control_mappings[randint(lim)]);
        Scene* scene5 = new Scene(room8, control_mappings[randint(lim)]);
        Scene* scene6 = new Scene(room6, control_mappings[randint(lim)]);
        Scene* scene7 = new Scene(room8, control_mappings[randint(lim)]);
        Scene* scene8 = new Scene(room1, control_mappings[randint(lim)]);
        Scene* scene9 = new Scene(room2, control_mappings[randint(lim)]);
        Scene* scene10 = new Scene(room4, control_mappings[randint(lim)]);
        Scene* scene11 = new Scene(room3);
        Scene* scene12 = new Scene(room4, control_mappings[randint(lim)]);
        Scene* scene13 = new Scene(room8, control_mappings[randint(lim)]);
        Scene* scene14 = new Scene(room6, control_mappings[randint(lim)]);

        start->linkScene(Direction::LEFT, scene0);
        scene0->linkScene(Direction::UP, scene1);
        scene0->linkScene(Direction::DOWN, scene6);
        scene1->linkScene(Direction::LEFT, scene2);
        scene1->linkScene(Direction::RIGHT, scene5);
        scene2->linkScene(Direction::UP, scene3);
        scene3->linkScene(Direction::RIGHT, scene4);
        scene4->linkScene(Direction::DOWN, scene5);
        scene6->linkScene(Direction::RIGHT, scene7);
        scene6->linkScene(Direction::LEFT, scene9);
        scene7->linkScene(Direction::UP, scene8);
        scene8->linkScene(Direction::RIGHT, scene10);
        scene9->linkScene(Direction::LEFT, scene10);
        scene9->linkScene(Direction::DOWN, scene13);
        scene10->linkScene(Direction::DOWN, scene11);
        scene11->linkScene(Direction::RIGHT, scene12);
        scene12->linkScene(Direction::RIGHT, scene13);
        scene12->linkScene(Direction::DOWN, scene14);
        scene14->linkScene(Direction::RIGHT, podroom);
    }
    default: 
        // Use seed to randomly generate world
        // TODO: implement
        break;

    }
    return world;
}